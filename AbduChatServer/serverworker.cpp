#include "serverworker.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>

#include <AbduChatLib/datastream.h>

ServerWorker::ServerWorker(QObject *parent)
    : QObject{parent}
    , serverSocket_{new QTcpSocket{this}}
    , user_(new User)
{
    connect(serverSocket_, &QTcpSocket::readyRead, this, &ServerWorker::receiveJson);
    connect(serverSocket_, &QTcpSocket::disconnected, this, &ServerWorker::disconnectedFromClient);
    connect(serverSocket_, &QTcpSocket::errorOccurred, this, &ServerWorker::errorOccurred);
}

bool ServerWorker::setSocketDescriptor(quintptr handle)
{
    return serverSocket_->setSocketDescriptor(handle);
}

void ServerWorker::sendJson(const QJsonObject &jsonObject)
{
    const QByteArray jsonData = QJsonDocument(jsonObject).toJson();

    DataStream socketStream(serverSocket_);
    socketStream << jsonData;

    emit logMessage("Sending to \'" + user()->username() + "\'-" + peerAddress() + " - " + QString::fromUtf8(jsonData));
}

QString ServerWorker::peerAddress() const
{
    return serverSocket_->peerAddress().toString();
}

QString ServerWorker::peerName() const
{
    return serverSocket_->peerName();
}

const UserPtr &ServerWorker::user() const
{
    return user_;
}

void ServerWorker::setUser(const UserPtr &newUser)
{
    if (user_ == newUser)
        return;
    user_ = newUser;
    emit userChanged();
}

void ServerWorker::resetUser()
{
    setUser({}); // TODO: Adapt to use your actual default value
}

void ServerWorker::disconnectFromClient()
{
    serverSocket_->disconnectFromHost();
}

void ServerWorker::receiveJson()
{
    QByteArray jsonData;
    DataStream socketStream(serverSocket_);

    forever {
        socketStream.startTransaction();
        socketStream >> jsonData;

        if (socketStream.commitTransaction()) {
            QJsonParseError parseError;
            QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData, &parseError);

            if (parseError.error == QJsonParseError::NoError) {

                if (jsonDocument.isObject()) {
                    emit jsonReceived(jsonDocument.object());
                } else {
                    emit logMessage("Invalid message received: " + QString::fromUtf8(jsonData));
                }

            } else {
                emit logMessage("Invalid message received: " + QString::fromUtf8(jsonData));
            }

        } else {
            break;
        }
    }
}
