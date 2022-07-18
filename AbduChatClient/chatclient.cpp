#include "chatclient.h"

#include <AbduChatLib/request_and_reply_constants.h>
#include <AbduChatLib/database_names.h>
#include <AbduChatLib/sqldatabaseclient.h>
#include <AbduChatLib/chatsviewtable.h>
#include <AbduChatLib/user.h>
#include <AbduChatLib/chat.h>
#include <AbduChatLib/message.h>
#include <AbduChatLib/datastream.h>
#include <AbduChatLib/logger.h>

#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlQuery>
#include <QSqlError>
#include <QJSValue>
#include <QScopedPointer>

const char* IpAddress = "127.0.0.1";
const int Port = 2002;

QString lastDateFromUsersTable()
{
    const QString execute = QString("SELECT %1 FROM %2 ORDER BY %3 DESC LIMIT 1")
                            .arg(db::users::fieldnames::Date)
                            .arg(db::users::TableName)
                            .arg(db::users::fieldnames::Id);
    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot get last insert datetime: %s", qPrintable(query.lastError().text()));
    }
    query.next();
    return query.value(0).toString();
}

QString lastDateFromMessagesTable()
{
    const QString execute = QString("SELECT %1 FROM %2 ORDER BY %3 DESC LIMIT 1")
                            .arg(db::messages::fieldnames::Date)
                            .arg(db::messages::TableName)
                            .arg(db::messages::fieldnames::Id);
    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot get last sent datetime: %s", qPrintable(query.lastError().text()));
    }
    query.next();
    return query.value(0).toString();
}

int usersTableRowCount()
{
    const QString execute = QString("SELECT COUNT(*) FROM %1").arg(db::users::TableName);
    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot get contacts table row count: %s", qPrintable(query.lastError().text()));
    }
    query.next();
    return query.value(0).toInt();
}

int messagesTableRowCount()
{
    const QString execute = QString("SELECT COUNT(*) FROM %1").arg(db::messages::TableName);
    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot get messages table row count: %s", qPrintable(query.lastError().text()));
    }
    query.next();
    return query.value(0).toInt();
}

ChatClient::ChatClient(SqlDatabaseClient *database, QObject *parent)
    : QObject{parent}
    , socket_(new QTcpSocket(this))
    , user_(new User(this))
    , database_(database)
{
    connect(socket_, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(socket_, &QTcpSocket::disconnected, this, &ChatClient::disconnected);
    connect(socket_, &QTcpSocket::disconnected, this, &ChatClient::resetUser);
    connect(socket_, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    connect(socket_, &QTcpSocket::errorOccurred, this, [this]() {emit errorOccurred(socket_->errorString());});
}

User *ChatClient::user() const
{
    return user_;
}

void ChatClient::setUser(const UserPtr &newUser)
{
    if (user_ == newUser)
        return;
    user_->copyValues(newUser);
    emit userChanged();
}

void ChatClient::resetUser()
{
    UserPtr emptyUser(new User);
    setUser(emptyUser);
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

void ChatClient::attempToRegister(const User &userInfo, const QString &password)
{
    QJsonObject info = userInfo.toJson();
    info[request::headers::Password] = password;

    QJsonObject registerInfo;
    registerInfo[request::headers::Type]         = request::types::Register;
    registerInfo[request::headers::RegisterInfo] = info;

    sendRequest(registerInfo);
}

void ChatClient::sendMessage(const QJSValue &chat, const QString &messageText)
{
    Logger::debug("ChatClient::sendMessage");
    Q_ASSERT(qobject_cast<Chat*>(chat.toQObject()));

    Message message;
    // 'id' and 'date' is get from server. So we dont need to specify it.
    message.setFrom(user_);
    message.setChat(qobject_cast<Chat*>(chat.toQObject()));
    message.setText(messageText);

    QJsonObject messageInfo;
    messageInfo[request::headers::Type]    = request::types::SendMessage;
    messageInfo[request::headers::Message] = message.toJson();

    sendRequest(messageInfo);
}

void ChatClient::requestCreateChat(int user2Id)
{
    Chat chat;
    chat.setType("private");
    chat.setUser1Id(user()->id()); // my id
    chat.setUser2Id(user2Id);
    qDebug() << "Chat Info " << QString::fromUtf8(QJsonDocument(chat.toJson()).toJson());

    QJsonObject createChatInfo;
    createChatInfo[request::headers::Type] = request::types::CreateChat;
    createChatInfo[request::headers::Chat] = chat.toJson();

    sendRequest(createChatInfo);
}

void ChatClient::synchronizeAll()
{
    synchronizeUsers();
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
    } else if (messageType == reply::types::ChatAdd) {
        parseChatAddReply(jsonReply);
    } else if (messageType == reply::types::UserList) {
        parseSynchronizeUsersReply(jsonReply);
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
        UserPtr user(User::fromJson(jsonReply.value(reply::headers::User).toObject()));
        setUser(user);
        emit loggedIn();
    }
}

void ChatClient::parseMessageReply(const QJsonObject &jsonReply)
{
    MessagePtr message(Message::fromJson(jsonReply.value(reply::headers::Message).toObject()));

    database_->addMessage(message);
}

void ChatClient::parseChatAddReply(const QJsonObject &jsonReply)
{
    const QJsonObject chatJson = jsonReply.value(reply::headers::Chat).toObject();
    const ChatPtr chat(Chat::fromJson(chatJson));
    database_->addChat(chat);
    database_->chatsViewTable()->select();
}

void ChatClient::parseSynchronizeUsersReply(const QJsonObject &jsonReply)
{
    const QJsonArray users = jsonReply.value(reply::headers::Users).toArray();
    if (!users.isEmpty()) {
        database_->addUsers(users);
    }
}

void ChatClient::parseSynchronizeMessagesReply(const QJsonObject &jsonReply)
{
    const QJsonArray messages = jsonReply.value(reply::headers::Messages).toArray();
    if (!messages.isEmpty()) {
        database_->addMessages(messages);
    }
}

void ChatClient::synchronizeUsers()
{
    QJsonObject synchronizeInfo;
    synchronizeInfo[request::headers::Type] = request::types::SynchronizeUsers;
    synchronizeInfo[request::headers::Date] = usersTableRowCount() > 0 ? lastDateFromUsersTable()
                                                                       : request::values::AllData;
    sendRequest(synchronizeInfo);
}

void ChatClient::synchronizeMessages()
{
    QJsonObject synchronizeInfo;
    synchronizeInfo[request::headers::Type] = request::types::SynchronizeMessages;
    synchronizeInfo[request::headers::Date] = messagesTableRowCount() > 0 ? lastDateFromMessagesTable()
                                                                          : request::values::AllData;

    sendRequest(synchronizeInfo);
}

void ChatClient::sendRequest(const QJsonObject &jsonRequest)
{
    DataStream socketStream(socket_);
    socketStream << jsonRequest;
}
