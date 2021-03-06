#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>

#include <AbduChatLib/user.h>
#include <AbduChatLib/chat.h>
#include <AbduChatLib/message.h>

class QJSValue;

class ChatClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(User* user READ user NOTIFY userChanged)
public:
    User* user() const;
    void setUser(const UserPtr& newUser);
    void resetUser();

    static ChatClient& instance();

signals:
    void connected();
    void disconnected();
    void errorOccurred(const QString& errorString);

    void loggedIn();
    void loginError(const QString& reason);

    void userChanged();

public slots:
    void connectToHost();
    void disconnectFromHost();

    void attempToLogIn(const QString& username, const QString& password);
    void attempToRegister(const User& userInfo, const QString& password);

    void sendMessage(const QJSValue& chat, const QString& messageText);

    void requestCreateChat(int user2Id);

    void synchronizeAll();

private slots:
    void onReadyRead();

private:
    explicit ChatClient(QObject *parent = nullptr);

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
    User* user_;
};

#endif // CHATCLIENT_H
