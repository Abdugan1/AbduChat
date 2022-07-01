#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>

#include <AbduChatLib/user.h>
#include <AbduChatLib/chat.h>
#include <AbduChatLib/messagestable.h>

class ServerWorker;
class SqlDatabaseServer;
class UsersTable;
class UsersServerTable;
class ServerLogsTable;
class MessagesTable;

class QMutex;

class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ChatServer(SqlDatabaseServer* database, QMutex* serverLogsMutex, QObject* parent = nullptr);
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
    void sendLogInSucceedReply(ServerWorker* recipient, const UserPtr& user);
    void sendLogInFailedReply(ServerWorker* recipient);

    void parseRegisterRequest(ServerWorker* sender, const QJsonObject& jsonRequest);
    void sendRegisterSucceedReply(ServerWorker* recipient);
    void sendRegisterFailedReply(ServerWorker* recipient);

    void parseSendMessageRequest(ServerWorker* sender, const QJsonObject& jsonRequest);
    void sendMessageReply(ServerWorker* recipient, const MessagePtr& message);

    void parseSynchronizeUsersRequest(ServerWorker* sender, const QJsonObject& jsonRequest);
    void sendAllUsersReply(ServerWorker* recipient);
    void sendNewerUsersAfterDatetimeReply(ServerWorker* recipient, const QString& insertDatetime);

    void parseSynchronizeMessagesRequest(ServerWorker* sender, const QJsonObject& jsonRequest);
    void sendAllMessagesReply(ServerWorker* recipient);
    void sendNewerMessagesAfterDatetimeReply(ServerWorker* recipient, const QString& sentDatetime);

    void parseCreateChatRequest(ServerWorker* sender, const QJsonObject& jsonRequest);
    void sendAddedChatReply(ServerWorker* recipient, const ChatPtr& chat);

    void broadcast(const QJsonObject& message, const ServerWorker* exclude);

private:
    QList<ServerWorker*> clients_;

    SqlDatabaseServer* database_ = nullptr;

    UsersTable*       usersTable_       = nullptr;
    UsersServerTable* usersServerTable_ = nullptr;
    ServerLogsTable*  serverLogsTable_  = nullptr;
    MessagesTable*    messagesTable_    = nullptr;

    QMutex* serverLogsMutex_ = nullptr;
};

#endif // CHATSERVER_H
