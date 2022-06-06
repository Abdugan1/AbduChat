#include "chatclient.h"

#include <AbduChatLib/request_and_reply_constants.h>
#include <AbduChatLib/message.h>
#include <AbduChatLib/datastream.h>

#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>

const char* IpAddress = "127.0.0.1";
const int Port = 2002;

ChatClient::ChatClient(QObject *parent)
    : QObject{parent}
    , socket_(new QTcpSocket(this))
{
    connect(socket_, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(socket_, &QTcpSocket::disconnected, this, &ChatClient::disconnected);
    connect(socket_, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    connect(socket_, &QTcpSocket::errorOccurred, this, [this]() {emit errorOccurred(socket_->errorString());});
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
    DataStream socketStream(socket_);

    QJsonObject loginInfoJson;
    loginInfoJson[request::headers::Type] = request::types::Login;
    loginInfoJson[request::headers::Username] = username;
    loginInfoJson[request::headers::Password] = password;

    socketStream << loginInfoJson;
}

void ChatClient::attempToRegister(const QString &username, const QString &password)
{
    DataStream socketStream(socket_);

    QJsonObject registerInfoJson;
    registerInfoJson[request::headers::Type] = request::types::Register;
    registerInfoJson[request::headers::Username] = username;
    registerInfoJson[request::headers::Password] = password;

    socketStream << registerInfoJson;
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

void ChatClient::parseReply(const QJsonObject &jsonObject)
{
    QString messageType = jsonObject.value(reply::headers::Type).toString();

    if (messageType == reply::types::Login) {
        parseLogInReply(jsonObject);
    } else if (messageType == reply::types::Message) {
        parseMessageReply(jsonObject);
    }
}

void ChatClient::parseLogInReply(const QJsonObject &jsonObject)
{
    bool successLogIn = jsonObject.value(reply::headers::Success).toBool();

    if (successLogIn)
        emit loggedIn();
    else
        emit loginError(jsonObject.value(reply::headers::Reason).toString());
}

void ChatClient::parseMessageReply(const QJsonObject &jsonObject)
{
    const QDateTime sentDatetime = QDateTime::fromString(jsonObject.value(reply::headers::SentDatetime)
                                                         .toString(), Qt::ISODate);

    Message message;
    message.setId(jsonObject.value(reply::headers::MessageId).toInt());
    message.setFromUser(jsonObject.value(reply::headers::FromUser).toString());
    message.setToUser(jsonObject.value(reply::headers::ToUser).toString());
    message.setToUser(jsonObject.value(reply::headers::Text).toString());
    message.setSentDatetime(sentDatetime);

    emit messageReceived(message);
}
