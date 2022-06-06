#include "chatserver.h"
#include "serverworker.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include <QMutexLocker>

#include <AbduChatLib/request_and_reply_constants.h>
#include <AbduChatLib/userstable.h>
#include <AbduChatLib/serverlogstable.h>

const int Port = 2002;

ChatServer::ChatServer(QMutex *serverLogsMutex, QObject *parent)
    : QTcpServer{parent}
    , usersTable_(new UsersTable(this))
    , serverLogsTable_(new ServerLogsTable(this))
    , serverLogsMutex_(serverLogsMutex)
{

}

void ChatServer::start()
{
    listen(QHostAddress::Any, Port);
    logMessage("Server started.");
}

void ChatServer::stop()
{
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

void ChatServer::incomingConnection(qintptr handle)
{
    ServerWorker* client = new ServerWorker(this);

    if (!client->setSocketDescriptor(handle)) {
        client->deleteLater();
        return;
    }

//    connect(client, &ServerWorker::disconnectedFromClient, this, std::bind(&ChatServer::userDisconnected, this, client));
//    connect(client, &ServerWorker::errorOccurred, this, std::bind(&ChatServer::userError, this, client));
    connect(client, &ServerWorker::jsonReceived, this, std::bind(&ChatServer::parseJsonRequest, this, client, std::placeholders::_1));
    connect(client, &ServerWorker::logMessage, this, &ChatServer::logMessage);

    clients_.append(client);

    QString message = QString("New client connected\n"
                              "IP address: \"%1\"\n"
                              "Name: \"%2\"").arg(client->peerAddress()).arg(client->peerName());
    logMessage(message);
}

void ChatServer::parseJsonRequestFromAuthorized(ServerWorker *sender, const QJsonObject &jsonRequest)
{

}

void ChatServer::parseJsonRequestFromUnauthorized(ServerWorker *sender, const QJsonObject &jsonRequest)
{
    QString requestType = jsonRequest.value(request::headers::Type).toString();

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

    if (usersTable_->hasUser(username, password)) {
        sendLogInSucceedReply(sender, username);
    } else {
        sendLogInFailedReply(sender);
    }
}

void ChatServer::sendLogInSucceedReply(ServerWorker *recipient, const QString &username)
{
    QJsonObject logInSuccessReply;
    logInSuccessReply[reply::headers::Type]     = reply::types::Login;
    logInSuccessReply[reply::headers::Success]  = true;
    logInSuccessReply[reply::headers::Username] = username;

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

ServerLogsTable *ChatServer::serverLogsTable() const
{
    return serverLogsTable_;
}
