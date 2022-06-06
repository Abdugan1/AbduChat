#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>

class ServerWorker;

class UsersTable;
class ServerLogsTable;

class QMutex;

class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ChatServer(QMutex* serverLogsMutex, QObject* parent = nullptr);

    ServerLogsTable *serverLogsTable() const;

public slots:
    void start();
    void stop();

    void logMessage(const QString& text);

private slots:
    void parseJsonRequest(ServerWorker* sender, const QJsonObject& jsonRequest);

protected:
    void incomingConnection(qintptr handle) override;

private:
    void parseJsonRequestFromAuthorized(ServerWorker* sender, const QJsonObject& jsonRequest);
    void parseJsonRequestFromUnauthorized(ServerWorker* sender, const QJsonObject& jsonRequest);

    void parseLogInRequest(ServerWorker* sender, const QJsonObject jsonRequest);
    void sendLogInSucceedReply(ServerWorker* recipient, const QString& username);
    void sendLogInFailedReply(ServerWorker* recipient);

    void parseRegisterRequest(ServerWorker* sender, const QJsonObject& jsonRequest);
    void sendRegisterSucceedReply(ServerWorker* recipient, const QString& username);
    void sendRegisterFailedReply(ServerWorker* recipient);

private:
    QList<ServerWorker*> clients_;

    UsersTable* usersTable_ = nullptr;
    ServerLogsTable* serverLogsTable_ = nullptr;

    QMutex* serverLogsMutex_ = nullptr;
};

#endif // CHATSERVER_H
