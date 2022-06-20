#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <AbduChatLib/user.h>

#include <QObject>

class QTcpSocket;

class ServerWorker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWorker(QObject *parent = nullptr);

    bool setSocketDescriptor(quintptr handle);

    void sendJson(const QJsonObject& jsonObject);

    QString peerAddress() const;
    QString peerName() const;

    const User &user() const;
    void setUser(const User &newUser);
    void resetUser();

signals:
    void jsonReceived(const QJsonObject& jsonObject);
    void disconnectedFromClient();
    void errorOccurred();

    void logMessage(const QString& text);

    void userChanged();

public slots:
    void disconnectFromClient();

private:
    void receiveJson();

private:
    QTcpSocket* serverSocket_ = nullptr;
    User user_;

};

#endif // SERVERWORKER_H
