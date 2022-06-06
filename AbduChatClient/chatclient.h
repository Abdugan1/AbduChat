#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>

class Message;

class ChatClient : public QObject
{
    Q_OBJECT
public:
    explicit ChatClient(QObject *parent = nullptr);

signals:
    void connected();
    void disconnected();
    void errorOccurred(const QString& errorString);

    void loggedIn();
    void loginError(const QString& reason);

    void messageReceived(const Message& message);

public slots:
    void connectToHost();
    void disconnectFromHost();

    void attempToLogIn(const QString& username, const QString& password);
    void attempToRegister(const QString& username, const QString& password);

private slots:
    void onReadyRead();

private:
    void parseReply(const QJsonObject& jsonObject);
    void parseLogInReply(const QJsonObject& jsonObject);
    void parseMessageReply(const QJsonObject& jsonObject);

private:
    QTcpSocket* socket_ = nullptr;
};

#endif // CHATCLIENT_H
