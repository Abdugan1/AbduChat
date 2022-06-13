#include "serverworker.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>

#include <AbduChatLib/datastream.h>

ServerWorker::ServerWorker(QObject *parent)
    : QObject{parent}
    , serverSocket_{new QTcpSocket{this}}
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

    emit logMessage("Sending to \'" + username_ + "\'-" + peerAddress() + " - " + QString::fromUtf8(jsonData));
}

const QString &ServerWorker::username() const
{
    return username_;
}

void ServerWorker::setUsername(const QString &newUsername)
{
    username_ = newUsername;
}

QString ServerWorker::peerAddress() const
{
    return serverSocket_->peerAddress().toString();
}

QString ServerWorker::peerName() const
{
    return serverSocket_->peerName();
}

int ServerWorker::id() const
{
    return id_;
}

void ServerWorker::setId(int newId)
{
    id_ = newId;
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
