#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>

class Message;

class ChatClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
public:
    explicit ChatClient(QObject *parent = nullptr);

    const QString &username() const;
    void setUsername(const QString &newUsername);

    int id() const;
    void setId(int newId);

signals:
    void connected();
    void disconnected();
    void errorOccurred(const QString& errorString);

    void loggedIn();
    void loginError(const QString& reason);

    void messageReceived(const Message& message);

    void contactsAvailable(const QJsonArray& contacts);
    void messagesAvailable(const QJsonArray& messages);

    void usernameChanged();

    void idChanged();

public slots:
    void connectToHost();
    void disconnectFromHost();

    void attempToLogIn(const QString& username, const QString& password);
    void attempToRegister(const QString& username, const QString& password);

    void sendMessage(int recipientId, const QString& messageText);

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

    void clearData();

private:
    QTcpSocket* socket_ = nullptr;
    QString username_;
    int id_ = -1;
};

#endif // CHATCLIENT_H
