#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>

#include <AbduChatLib/user.h>

class Chat;
class Message;

class ChatClient : public QObject
{
    Q_OBJECT
public:
    explicit ChatClient(QObject *parent = nullptr);

    const User &user() const;
    void setUser(const User &newUser);
    void resetUser();

signals:
    void connected();
    void disconnected();
    void errorOccurred(const QString& errorString);

    void loggedIn();
    void loginError(const QString& reason);

    void messageReceived(const Message& message);

    void contactsAvailable(const QJsonArray& contacts);
    void messagesAvailable(const QJsonArray& messages);


public slots:
    void connectToHost();
    void disconnectFromHost();

    void attempToLogIn(const QString& username, const QString& password);
    void attempToRegister(const User& userInfo, const QString& password);

    void sendMessage(const Chat& chat, const QString& messageText);

    void synchronizeAll();

private slots:
    void onReadyRead();

private:
    void parseReply(const QJsonObject& jsonObject);
    void parseLogInReply(const QJsonObject& jsonObject);
    void parseMessageReply(const QJsonObject& jsonObject);
    void parseSynchronizeContactsReply(const QJsonObject& jsonReply);
    void parseSynchronizeMessagesReply(const QJsonObject& jsonReply);

    void synchronizeContacts();
    void synchronizeMessages();

    void sendRequest(const QJsonObject& jsonRequest);

private:
    QTcpSocket* socket_ = nullptr;
    User user_;
};

#endif // CHATCLIENT_H
