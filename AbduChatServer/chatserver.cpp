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
#include <AbduChatLib/sqldatabaseserver.h>
#include <AbduChatLib/usersservertable.h>
#include <AbduChatLib/serverlogstable.h>
#include <AbduChatLib/messagestableclient.h>
#include <AbduChatLib/message.h>

const int Port = 2002;

ChatServer::ChatServer(SqlDatabaseServer* database, QMutex *serverLogsMutex, QObject *parent)
    : QTcpServer{parent}
    , database_(database)
    , serverLogsMutex_(serverLogsMutex)
{
    usersServerTable_ = database_->usersServerTable();
    serverLogsTable_  = database_->serverLogsTable();
    messagesTable_    = database_->messagesTable();
}

ChatServer::~ChatServer()
{
    if (isListening())
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
            .arg(sender->user().username())
            .arg(sender->peerAddress())
            .arg(QString(QJsonDocument(jsonRequest).toJson()));

    logMessage(log);

    if (!sender->user().isValid()) {
        parseJsonRequestFromUnauthorized(sender, jsonRequest);
    } else {
        parseJsonRequestFromAuthorized(sender, jsonRequest);
    }
}

void ChatServer::onUserDisconnected(ServerWorker *client)
{
    clients_.removeAll(client);
    if (client->user().isValid()) {
        QJsonObject disconnectedMessage;
        disconnectedMessage[reply::headers::Type] = reply::types::UserDisconnected;
        disconnectedMessage[reply::headers::User]   = client->user().toJson();
        broadcast(disconnectedMessage, nullptr);

        logMessage(QString("%1 disconnected.\nIP: %2\nName: %3")
                   .arg(client->user().username(), client->peerAddress(), client->peerName()));
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

    if (!usersServerTable_->hasUser(username, password)) {
        sendLogInFailedReply(sender);
    } else {
        User user = User::fromSqlRecord(usersServerTable_->getUser(username));
        sendLogInSucceedReply(sender, user);
        sender->setUser(user);
    }
}

void ChatServer::sendLogInSucceedReply(ServerWorker *recipient, const User& user)
{
    QJsonObject logInSuccessReply;
    logInSuccessReply[reply::headers::Type]     = reply::types::Login;
    logInSuccessReply[reply::headers::Success]  = true;
    logInSuccessReply[reply::headers::User]     = user.toJson();

    recipient->sendJson(logInSuccessReply);
}

void ChatServer::sendLogInFailedReply(ServerWorker *recipient)
{
    QJsonObject logInFailedReply;
    logInFailedReply[reply::headers::Type]      = reply::types::Login;
    logInFailedReply[reply::headers::Success]   = false;
    logInFailedReply[reply::headers::Reason]    = reply::values::LoginFailed;

    recipient->sendJson(logInFailedReply);
}

void ChatServer::parseRegisterRequest(ServerWorker *sender, const QJsonObject &jsonRequest)
{
    const User user = User::fromJson(jsonRequest);
    const QString password = jsonRequest.value(request::headers::Password).toString();

    if (database_->addUser(user, password)) {
        sendRegisterSucceedReply(sender);
    } else {
        sendRegisterFailedReply(sender);
    }
}

void ChatServer::sendRegisterSucceedReply(ServerWorker *recipient)
{
    QJsonObject registerSuccessReply;
    registerSuccessReply[reply::headers::Type]     = reply::types::Register;
    registerSuccessReply[reply::headers::Success]  = true;

    recipient->sendJson(registerSuccessReply);
}

void ChatServer::sendRegisterFailedReply(ServerWorker *recipient)
{
    QJsonObject registerFailedReply;
    registerFailedReply[reply::headers::Type]      = reply::types::Register;
    registerFailedReply[reply::headers::Success]   = false;
    registerFailedReply[reply::headers::Reason]    = reply::values::UsernameIsUsed;

    recipient->sendJson(registerFailedReply);
}

void ChatServer::parseSendMessageRequest(ServerWorker *sender, const QJsonObject &jsonRequest)
{
    Message message = Message::fromJson(jsonRequest);
    database_->addMessage(message);

    // last inserted message id.
    message.setId(messagesTable_->record(messagesTable_->rowCount() - 1)
                  .value(db::messages::fieldnames::Id).toInt());

    sendMessageReply(sender, message);
}

void ChatServer::sendMessageReply(ServerWorker *recipient, const Message &message)
{
    QJsonObject messageReply;
    messageReply[reply::headers::Type]    = reply::types::Message;
    messageReply[reply::headers::Message] = message.toJson();

    recipient->sendJson(messageReply);
}

void ChatServer::parseSynchronizeContactsRequest(ServerWorker *sender, const QJsonObject &jsonRequest)
{
    const QString lastDate = jsonRequest[request::headers::Date].toString();

    if (lastDate == request::values::AllData) {
        sendAllContactsReply(sender);
    } else {
        const QString insertDatetime = jsonRequest.value(request::headers::Date).toString();
        sendNewerContactsAfterDatetimeReply(sender, insertDatetime);
    }
}

void ChatServer::sendAllContactsReply(ServerWorker *recipient)
{
    QJsonArray users;

    const int rowCount = usersServerTable_->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        const QSqlRecord record = usersServerTable_->record(i);
        QJsonObject user = User::fromSqlRecord(record).toJson();
        users.push_back(user);
    }

    QJsonObject contactsReply;
    contactsReply[reply::headers::Type]  = reply::types::UserList;
    contactsReply[reply::headers::Users] = users;

    recipient->sendJson(contactsReply);
}

void ChatServer::sendNewerContactsAfterDatetimeReply(ServerWorker *recipient, const QString &insertDatetime)
{
    const QString execute = QString("SELECT * FROM users WHERE %1 > :date")
                            .arg(db::users::fieldnames::Date);

    QSqlQuery query;
    query.prepare(execute);
    query.bindValue(":date", insertDatetime);

    if (!query.exec()) {
        qFatal("Cannot get last contacts from %s: %s",
               qPrintable(insertDatetime), qPrintable(query.lastError().text()));
    }

    QJsonArray users;
    while (query.next()) {
        // TODO: Check info about value() and record()
        QJsonObject contact = User::fromSqlRecord(query.record()).toJson();

        users.push_back(contact);
    }

    QJsonObject contactsReply;
    contactsReply[reply::headers::Type]  = reply::types::UserList;
    contactsReply[reply::headers::Users] = users;

    recipient->sendJson(contactsReply);
}

void ChatServer::parseSynchronizeMessagesRequest(ServerWorker *sender, const QJsonObject &jsonRequest)
{
    const QString lastSentDatetime = jsonRequest[request::headers::Date].toString();

    if (lastSentDatetime == request::values::AllData) {
        sendAllMessagesReply(sender);
    } else {
        const QString sentDatetime = jsonRequest.value(request::headers::Date).toString();
        sendNewerMessagesAfterDatetimeReply(sender, sentDatetime);
    }
}

void ChatServer::sendAllMessagesReply(ServerWorker *recipient)
{
    QJsonArray messages;
    const int rowCount = messagesTable_->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        const QSqlRecord record = messagesTable_->record(i);
        QJsonObject message = Message::fromSqlRecord(record).toJson();
        messages.push_back(message);
    }

    QJsonObject messagesReply;
    messagesReply[reply::headers::Type]     = reply::types::MessageList;
    messagesReply[reply::headers::Messages] = messages;

    recipient->sendJson(messagesReply);
}

void ChatServer::sendNewerMessagesAfterDatetimeReply(ServerWorker *recipient, const QString &sentDatetime)
{
    const QString execute = QString("SELECT * FROM messages WHERE %1 > :date")
            .arg(db::messages::fieldnames::Date);

    QSqlQuery query;
    query.prepare(execute);
    query.bindValue(":date", sentDatetime);

    if (!query.exec()) {
        qFatal("Cannot get last messages from %s: %s",
               qPrintable(sentDatetime), qPrintable(query.lastError().text()));
    }

    QJsonArray messages;
    while (query.next()) {
        // TODO: Check info about value() and record()
        QJsonObject message = Message::fromSqlRecord(query.record()).toJson();

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
