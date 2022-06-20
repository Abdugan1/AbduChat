#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>

class ServerWorker;
class User;

class SqlDatabase;
class UsersServerTable;
class ServerLogsTable;
class MessagesTable;
class Message;

class QMutex;

class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ChatServer(SqlDatabase* database, QMutex* serverLogsMutex, QObject* parent = nullptr);
    ~ChatServer();

    ServerLogsTable *serverLogsTable() const;

public slots:
    void start();
    void stop();

    void logMessage(const QString& text);

private slots:
    void parseJsonRequest(ServerWorker* sender, const QJsonObject& jsonRequest);

    void onUserDisconnected(ServerWorker* client);

protected:
    void incomingConnection(qintptr handle) override;

private:
    void parseJsonRequestFromAuthorized(ServerWorker* sender, const QJsonObject& jsonRequest);
    void parseJsonRequestFromUnauthorized(ServerWorker* sender, const QJsonObject& jsonRequest);

    void parseLogInRequest(ServerWorker* sender, const QJsonObject jsonRequest);
    void sendLogInSucceedReply(ServerWorker* recipient, const User& user);
    void sendLogInFailedReply(ServerWorker* recipient);

    void parseRegisterRequest(ServerWorker* sender, const QJsonObject& jsonRequest);
    void sendRegisterSucceedReply(ServerWorker* recipient);
    void sendRegisterFailedReply(ServerWorker* recipient);

    void parseSendMessageRequest(ServerWorker* sender, const QJsonObject& jsonRequest);
    void sendMessageReply(ServerWorker* recipient, const Message& message);

    void parseSynchronizeContactsRequest(ServerWorker* sender, const QJsonObject& jsonRequest);
    void sendAllContactsReply(ServerWorker* recipient);
    void sendNewerContactsAfterDatetimeReply(ServerWorker* recipient, const QString& insertDatetime);

    void parseSynchronizeMessagesRequest(ServerWorker* sender, const QJsonObject& jsonRequest);
    void sendAllMessagesReply(ServerWorker* recipient);
    void sendNewerMessagesAfterDatetimeReply(ServerWorker* recipient, const QString& sentDatetime);

    void broadcast(const QJsonObject& message, const ServerWorker* exclude);

private:
    QList<ServerWorker*> clients_;

    SqlDatabase* database_ = nullptr;

    UsersServerTable* usersServerTable_ = nullptr;
    ServerLogsTable*  serverLogsTable_  = nullptr;
    MessagesTable*    messagesTable_    = nullptr;

    QMutex* serverLogsMutex_ = nullptr;
};

#endif // CHATSERVER_H
