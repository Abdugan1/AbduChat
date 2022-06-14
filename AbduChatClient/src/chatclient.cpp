#include "chatclient.h"

#include <AbduChatLib/request_and_reply_constants.h>
#include <AbduChatLib/message.h>
#include <AbduChatLib/datastream.h>

#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlQuery>
#include <QSqlError>

const char* IpAddress = "127.0.0.1";
const int Port = 2002;

QString lastInsertDatetimeContactsTable()
{
    const QString execute = QString("SELECT insert_datetime FROM contacts ORDER BY id DESC LIMIT 1");
    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot get last insert datetime: %s", qPrintable(query.lastError().text()));
    }
    query.next();
    return query.value(0).toString();
}

QString lastSentDatetimeMessagesTable()
{
    const QString execute = QString("SELECT sent_datetime FROM messages ORDER BY id DESC LIMIT 1");
    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot get last sent datetime: %s", qPrintable(query.lastError().text()));
    }
    query.next();
    return query.value(0).toString();
}

int contactsTableRowCount()
{
    const QString execute = QString("SELECT COUNT(*) FROM contacts");
    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot get contacts table row count: %s", qPrintable(query.lastError().text()));
    }
    query.next();
    return query.value(0).toInt();
}

int messagesTableRowCount()
{
    const QString execute = QString("SELECT COUNT(*) FROM messages");
    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot get messages table row count: %s", qPrintable(query.lastError().text()));
    }
    query.next();
    return query.value(0).toInt();
}

ChatClient::ChatClient(QObject *parent)
    : QObject{parent}
    , socket_(new QTcpSocket(this))
{
    connect(socket_, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(socket_, &QTcpSocket::disconnected, this, &ChatClient::disconnected);
    connect(socket_, &QTcpSocket::disconnected, this, &ChatClient::clearData);
    connect(socket_, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    connect(socket_, &QTcpSocket::errorOccurred, this, [this]() {emit errorOccurred(socket_->errorString());});
}

const QString &ChatClient::username() const
{
    return username_;
}

void ChatClient::setUsername(const QString &newUsername)
{
    if (username_ == newUsername)
        return;
    username_ = newUsername;
    emit usernameChanged();
}

int ChatClient::id() const
{
    return id_;
}

void ChatClient::setId(int newId)
{
    if (id_ == newId)
        return;
    id_ = newId;
    emit idChanged();
}

void ChatClient::connectToHost()
{
    socket_->connectToHost(QHostAddress(IpAddress), Port);
}

void ChatClient::disconnectFromHost()
{
    socket_->disconnectFromHost();
}

void ChatClient::attempToLogIn(const QString &username, const QString &password)
{
    QJsonObject loginInfo;
    loginInfo[request::headers::Type] = request::types::Login;
    loginInfo[request::headers::Username] = username;
    loginInfo[request::headers::Password] = password;

    sendRequest(loginInfo);
}

void ChatClient::attempToRegister(const QString &username, const QString &password)
{
    QJsonObject registerInfo;
    registerInfo[request::headers::Type] = request::types::Register;
    registerInfo[request::headers::Username] = username;
    registerInfo[request::headers::Password] = password;

    sendRequest(registerInfo);
}

void ChatClient::sendMessage(int recipientId, const QString &messageText)
{
    QJsonObject messageInfo;
    messageInfo[request::headers::Type]     = request::types::SendMessage;
    messageInfo[request::headers::Text]     = messageText;
    messageInfo[request::headers::FromUserId] = id();
    messageInfo[request::headers::ToUserId]   = recipientId;

    sendRequest(messageInfo);
}

void ChatClient::synchronizeAll()
{
    synchronizeContacts();
    synchronizeMessages();
}

void ChatClient::onReadyRead()
{
    QByteArray jsonData;
    DataStream socketStream(socket_);

    forever {
        socketStream.startTransaction();
        socketStream >> jsonData;

        if (!socketStream.commitTransaction())
            break;

        QJsonParseError parseError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData, &parseError);

        if (parseError.error == QJsonParseError::NoError && jsonDocument.isObject())
            parseReply(jsonDocument.object());
    }
}

void ChatClient::parseReply(const QJsonObject &jsonReply)
{
    QString messageType = jsonReply.value(reply::headers::Type).toString();

    if (messageType == reply::types::Login) {
        parseLogInReply(jsonReply);
    } else if (messageType == reply::types::Message) {
        parseMessageReply(jsonReply);
    } else if (messageType == reply::types::UserList) {
        parseSynchronizeContactsReply(jsonReply);
    } else if (messageType == reply::types::MessageList) {
        parseSynchronizeMessagesReply(jsonReply);
    }
}

void ChatClient::parseLogInReply(const QJsonObject &jsonReply)
{
    bool successLogIn = jsonReply.value(reply::headers::Success).toBool();

    if (!successLogIn) {
        emit loginError(jsonReply.value(reply::headers::Reason).toString());
    } else {
        setUsername(jsonReply.value(reply::headers::Username).toString());
        setId(jsonReply.value(reply::headers::Id).toInt());
        emit loggedIn();
    }
}

void ChatClient::parseMessageReply(const QJsonObject &jsonReply)
{
    Message message;
    message.setId(jsonReply.value(reply::headers::Id).toInt());
    message.setFromUserId(jsonReply.value(reply::headers::FromUserId).toInt());
    message.setToUserId(jsonReply.value(reply::headers::ToUserId).toInt());
    message.setText(jsonReply.value(reply::headers::Text).toString());
    message.setSentDatetime(jsonReply.value(reply::headers::SentDatetime).toString());

    emit messageReceived(message);
}

void ChatClient::parseSynchronizeContactsReply(const QJsonObject &jsonReply)
{
    const QJsonArray contacts = jsonReply.value(reply::headers::Users).toArray();
    if (!contacts.isEmpty()) {
        emit contactsAvailable(contacts);
    }
}

void ChatClient::parseSynchronizeMessagesReply(const QJsonObject &jsonReply)
{
    const QJsonArray messages = jsonReply.value(reply::headers::Messages).toArray();
    if (!messages.isEmpty()) {
        emit messagesAvailable(messages);
    }
}

void ChatClient::synchronizeContacts()
{
    QJsonObject synchronizeInfo;
    synchronizeInfo[request::headers::Type]           = request::types::SynchronizeContacts;
    synchronizeInfo[request::headers::InsertDatetime] = contactsTableRowCount() > 0 ? lastInsertDatetimeContactsTable()
                                                                                    : request::values::AllData;
    sendRequest(synchronizeInfo);
}

void ChatClient::synchronizeMessages()
{
    QJsonObject synchronizeInfo;
    synchronizeInfo[request::headers::Type]         = request::types::SynchronizeMessages;
    synchronizeInfo[request::headers::SentDatetime] = messagesTableRowCount() > 0 ? lastSentDatetimeMessagesTable()
                                                                                  : request::values::AllData;

    sendRequest(synchronizeInfo);
}

void ChatClient::sendRequest(const QJsonObject &jsonRequest)
{
    DataStream socketStream(socket_);
    socketStream << jsonRequest;
}

void ChatClient::clearData()
{
    setUsername("");
    setId(-1);
}
