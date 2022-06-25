#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>

#include <AbduChatLib/user.h>

class Chat;
class Message;

class SqlDatabaseClient;

class ChatClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int myUserId READ myUserId CONSTANT)
public:
    explicit ChatClient(SqlDatabaseClient* database, QObject *parent = nullptr);

    const User &user() const;
    void setUser(const User &newUser);
    void resetUser();

    int myUserId() const;

signals:
    void connected();
    void disconnected();
    void errorOccurred(const QString& errorString);

    void loggedIn();
    void loginError(const QString& reason);

    void messageReceived(const Message& message);

    void messagesAvailable(const QJsonArray& messages);


public slots:
    void connectToHost();
    void disconnectFromHost();

    void attempToLogIn(const QString& username, const QString& password);
    void attempToRegister(const User& userInfo, const QString& password);

    void sendMessage(const Chat& chat, const QString& messageText);

    void requestCreateChat(int user2Id);

    void synchronizeAll();

private slots:
    void onReadyRead();

private:
    void parseReply(const QJsonObject& jsonReply);
    void parseLogInReply(const QJsonObject& jsonReply);
    void parseMessageReply(const QJsonObject& jsonReply);
    void parseChatAddReply(const QJsonObject& jsonReply);
    void parseSynchronizeUsersReply(const QJsonObject& jsonReply);
    void parseSynchronizeMessagesReply(const QJsonObject& jsonReply);

    void synchronizeUsers();
    void synchronizeMessages();

    void sendRequest(const QJsonObject& jsonRequest);

private:
    QTcpSocket* socket_ = nullptr;
    User user_;

    SqlDatabaseClient* database_ = nullptr;
};

#endif // CHATCLIENT_H
