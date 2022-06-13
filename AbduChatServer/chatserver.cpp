#include "chatserver.h"
#include "serverworker.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDateTime>
#include <QMutexLocker>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include <AbduChatLib/request_and_reply_constants.h>
#include <AbduChatLib/database_names.h>
#include <AbduChatLib/userstable.h>
#include <AbduChatLib/serverlogstable.h>
#include <AbduChatLib/messagestableserver.h>
#include <AbduChatLib/message.h>

const int Port = 2002;

ChatServer::ChatServer(QMutex *serverLogsMutex, QObject *parent)
    : QTcpServer{parent}
    , usersTable_(new UsersTable(this))
    , serverLogsTable_(new ServerLogsTable(this))
    , messagesTable_(new MessagesTableServer(this))
    , serverLogsMutex_(serverLogsMutex)
{

}

ChatServer::~ChatServer()
{
    stop();
}

void ChatServer::start()
{
    listen(QHostAddress::Any, Port);
    logMessage("Server started.");
}

void ChatServer::stop()
{
    for (auto client : clients_) {
        client->disconnectFromClient();
        client->deleteLater();
    }
    clients_.clear();
    close();
    logMessage("Server stopped");
}

void ChatServer::logMessage(const QString &text)
{
    QMutexLocker serverLogsLocker(serverLogsMutex_);
    serverLogsTable_->insertLog(text, QDateTime::currentDateTime().toString(Qt::ISODate));
}

void ChatServer::parseJsonRequest(ServerWorker *sender, const QJsonObject &jsonRequest)
{    
    const QString log = QString("JSON received from '%1'-%2: %3")
            .arg(sender->username())
            .arg(sender->peerAddress())
            .arg(QString(QJsonDocument(jsonRequest).toJson()));

    logMessage(log);

    if (sender->username().isEmpty()) {
        parseJsonRequestFromUnauthorized(sender, jsonRequest);
    } else {
        parseJsonRequestFromAuthorized(sender, jsonRequest);
    }
}

void ChatServer::onUserDisconnected(ServerWorker *client)
{
    clients_.removeAll(client);
    if (client->id() != -1) {
        QJsonObject disconnectedMessage;
        disconnectedMessage[reply::headers::Type] = reply::types::UserDisconnected;
        disconnectedMessage[reply::headers::Id]   = client->id();
        broadcast(disconnectedMessage, nullptr);

        logMessage(QString("%1 disconnected.\nIP: %2\nName: %3")
                   .arg(client->username(), client->peerAddress(), client->peerName()));
    }
}

void ChatServer::incomingConnection(qintptr handle)
{
    ServerWorker* client = new ServerWorker(this);

    if (!client->setSocketDescriptor(handle)) {
        client->deleteLater();
        return;
    }

    connect(client, &ServerWorker::disconnectedFromClient,
            this,   std::bind(&ChatServer::onUserDisconnected, this, client));

//    connect(client, &ServerWorker::errorOccurred, this, std::bind(&ChatServer::userError, this, client));

    connect(client, &ServerWorker::jsonReceived,
            this,   std::bind(&ChatServer::parseJsonRequest, this, client, std::placeholders::_1));

    connect(client, &ServerWorker::logMessage, this, &ChatServer::logMessage);

    clients_.append(client);

    QString message = QString("New client connected\n"
                              "IP address: \"%1\"\n"
                              "Name: \"%2\"").arg(client->peerAddress(), client->peerName());
    logMessage(message);
}

void ChatServer::parseJsonRequestFromAuthorized(ServerWorker *sender, const QJsonObject &jsonRequest)
{
    const QString requestType = jsonRequest.value(request::headers::Type).toString();

    if (requestType == request::types::SendMessage) {
        parseSendMessageRequest(sender, jsonRequest);
    } else if (requestType == request::types::SynchronizeContacts) {
        parseSynchronizeContactsRequest(sender, jsonRequest);
    } else if (requestType == request::types::SynchronizeMessages) {
        parseSynchronizeMessagesRequest(sender, jsonRequest);
    }
}

void ChatServer::parseJsonRequestFromUnauthorized(ServerWorker *sender, const QJsonObject &jsonRequest)
{
    const QString requestType = jsonRequest.value(request::headers::Type).toString();

    if (requestType == request::types::Login) {
        parseLogInRequest(sender, jsonRequest);
    } else if (requestType == request::types::Register) {
        parseRegisterRequest(sender, jsonRequest);
    }
}

void ChatServer::parseLogInRequest(ServerWorker *sender, const QJsonObject jsonRequest)
{
    const QString username = jsonRequest.value(request::headers::Username).toString();
    const QString password = jsonRequest.value(request::headers::Password).toString();

    if (!usersTable_->hasUser(username, password)) {
        sendLogInFailedReply(sender);
    } else {
        int id = usersTable_->getUser(username).value(db::users::fieldnames::Id).toInt();
        sendLogInSucceedReply(sender, username, id);
        sender->setUsername(username);
        sender->setId(id);
    }
}

void ChatServer::sendLogInSucceedReply(ServerWorker *recipient, const QString &username, int id)
{
    QJsonObject logInSuccessReply;
    logInSuccessReply[reply::headers::Type]     = reply::types::Login;
    logInSuccessReply[reply::headers::Success]  = true;
    logInSuccessReply[reply::headers::Username] = username;
    logInSuccessReply[reply::headers::Id]       = id;

    recipient->sendJson(logInSuccessReply);
}

void ChatServer::sendLogInFailedReply(ServerWorker *recipient)
{
    QJsonObject logInFailedReply;
    logInFailedReply[reply::headers::Type]      = reply::types::Login;
    logInFailedReply[reply::headers::Success]   = false;
    logInFailedReply[reply::headers::Reason]    = "Login failed";

    recipient->sendJson(logInFailedReply);
}

void ChatServer::parseRegisterRequest(ServerWorker *sender, const QJsonObject &jsonRequest)
{
    const QString username = jsonRequest.value(request::headers::Username).toString();
    const QString password = jsonRequest.value(request::headers::Password).toString();

    if (usersTable_->insertUser(username, password)) {
        sendRegisterSucceedReply(sender, username);
    } else {
        sendRegisterFailedReply(sender);
    }
}

void ChatServer::sendRegisterSucceedReply(ServerWorker *recipient, const QString &username)
{
    QJsonObject registerSuccessReply;
    registerSuccessReply[reply::headers::Type]     = reply::types::Register;
    registerSuccessReply[reply::headers::Success]  = true;
    registerSuccessReply[reply::headers::Username] = username;

    recipient->sendJson(registerSuccessReply);
}

void ChatServer::sendRegisterFailedReply(ServerWorker *recipient)
{
    QJsonObject registerFailedReply;
    registerFailedReply[reply::headers::Type]      = reply::types::Register;
    registerFailedReply[reply::headers::Success]   = false;
    registerFailedReply[reply::headers::Reason]    = "The username is already in use";

    recipient->sendJson(registerFailedReply);
}

void ChatServer::parseSendMessageRequest(ServerWorker *sender, const QJsonObject &jsonRequest)
{
    Message message = jsonToMessageSentDatetimeIsCurrentDatetime(jsonRequest);
    messagesTable_->insertMessage(message);

    // last inserted message id.
    message.setId(messagesTable_->record(messagesTable_->rowCount() - 1)
                  .value(db::messages::fieldnames::MessageId).toInt());

    sendMessageReply(sender, message);
}

void ChatServer::sendMessageReply(ServerWorker *recipient, const Message &message)
{
    QJsonObject messageReply;
    messageReply[reply::headers::Type]          = reply::types::Message;
    messageReply[reply::headers::Id]            = message.id();
    messageReply[reply::headers::FromUserId]    = message.fromUserId();
    messageReply[reply::headers::ToUserId]      = message.toUserId();
    messageReply[reply::headers::Text]          = message.text();
    messageReply[reply::headers::SentDatetime]  = message.sentDatetime();

    recipient->sendJson(messageReply);
}

void ChatServer::parseSynchronizeContactsRequest(ServerWorker *sender, const QJsonObject &jsonRequest)
{
    const QString lastInsertDatetime = jsonRequest[request::headers::InsertDatetime].toString();

    if (lastInsertDatetime == request::values::AllData) {
        sendAllContactsReply(sender);
    } else {
        const QString insertDatetime = jsonRequest.value(request::headers::InsertDatetime).toString();
        sendNewerContactsAfterDatetimeReply(sender, insertDatetime);
    }
}

void ChatServer::sendAllContactsReply(ServerWorker *recipient)
{
    namespace FieldNames = db::contacts::fieldnames;

    QJsonArray contacts;
    int rowCount = usersTable_->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        const QSqlRecord record = usersTable_->record(i);
        QJsonObject contact;
        contact[reply::headers::Username] = record.value(FieldNames::Username).toString();
        contact[reply::headers::InsertDatetime] = record.value(FieldNames::InsertDatetime).toString();
        contacts.push_back(contact);
    }

    QJsonObject contactsReply;
    contactsReply[reply::headers::Type]  = reply::types::UserList;
    contactsReply[reply::headers::Users] = contacts;

    recipient->sendJson(contactsReply);
}

void ChatServer::sendNewerContactsAfterDatetimeReply(ServerWorker *recipient, const QString &insertDatetime)
{
    const QString execute = QString("SELECT * FROM users WHERE insert_datetime > :insert_datetime");

    QSqlQuery query;
    query.prepare(execute);
    query.bindValue(":insert_datetime", insertDatetime);

    if (!query.exec()) {
        qFatal("Cannot get last contacts from %s: %s",
               qPrintable(insertDatetime), qPrintable(query.lastError().text()));
    }

    namespace FieldNames = db::contacts::fieldnames;

    QJsonArray contacts;
    while (query.next()) {
        QJsonObject contact;
        contact[reply::headers::Username]       = query.value(FieldNames::Username).toString();
        contact[reply::headers::InsertDatetime] = query.value(FieldNames::InsertDatetime).toString();

        contacts.push_back(contact);
    }

    QJsonObject contactsReply;
    contactsReply[reply::headers::Type]  = reply::types::UserList;
    contactsReply[reply::headers::Users] = contacts;

    recipient->sendJson(contactsReply);
}

void ChatServer::parseSynchronizeMessagesRequest(ServerWorker *sender, const QJsonObject &jsonRequest)
{
    const QString lastSentDatetime = jsonRequest[request::headers::SentDatetime].toString();

    if (lastSentDatetime == request::values::AllData) {
        sendAllMessagesReply(sender);
    } else {
        const QString sentDatetime = jsonRequest.value(request::headers::SentDatetime).toString();
        sendNewerMessagesAfterDatetimeReply(sender, sentDatetime);
    }
}

void ChatServer::sendAllMessagesReply(ServerWorker *recipient)
{
    namespace FieldNames = db::messages::fieldnames;

    QJsonArray messages;
    int rowCount = messagesTable_->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        const QSqlRecord record = messagesTable_->record(i);
        QJsonObject message;
        message[reply::headers::Id]    = record.value(FieldNames::MessageId).toInt();
        message[reply::headers::FromUserId]     = record.value(FieldNames::FromUserId).toInt();
        message[reply::headers::ToUserId]       = record.value(FieldNames::ToUserId).toInt();
        message[reply::headers::Text]         = record.value(FieldNames::Text).toString();
        message[reply::headers::SentDatetime] = record.value(FieldNames::SentDatetime).toString();
        messages.push_back(message);
    }

    QJsonObject messagesReply;
    messagesReply[reply::headers::Type]     = reply::types::MessageList;
    messagesReply[reply::headers::Messages] = messages;

    recipient->sendJson(messagesReply);
}

void ChatServer::sendNewerMessagesAfterDatetimeReply(ServerWorker *recipient, const QString &sentDatetime)
{
    const QString execute = QString("SELECT * FROM messages WHERE sent_datetime > :sent_datetime");

    QSqlQuery query;
    query.prepare(execute);
    query.bindValue(":sent_datetime", sentDatetime);

    if (!query.exec()) {
        qFatal("Cannot get last messages from %s: %s",
               qPrintable(sentDatetime), qPrintable(query.lastError().text()));
    }

    namespace FieldNames = db::messages::fieldnames;

    QJsonArray messages;
    while (query.next()) {
        QJsonObject message;
        message[reply::headers::Id]    = query.value(FieldNames::MessageId).toInt();
        message[reply::headers::FromUserId]     = query.value(FieldNames::FromUserId).toInt();
        message[reply::headers::ToUserId]       = query.value(FieldNames::ToUserId).toInt();
        message[reply::headers::Text]         = query.value(FieldNames::Text).toString();
        message[reply::headers::SentDatetime] = query.value(FieldNames::SentDatetime).toString();

        messages.push_back(message);
    }

    QJsonObject messagesReply;
    messagesReply[reply::headers::Type]     = reply::types::MessageList;
    messagesReply[reply::headers::Messages] = messages;

    recipient->sendJson(messagesReply);
}

void ChatServer::broadcast(const QJsonObject &message, const ServerWorker *exclude)
{
    for (auto client : clients_) {
        if (client != exclude)
            client->sendJson(message);
    }
}

ServerLogsTable *ChatServer::serverLogsTable() const
{
    return serverLogsTable_;
}
