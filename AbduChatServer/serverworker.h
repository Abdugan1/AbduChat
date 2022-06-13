#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>

class QTcpSocket;

class ServerWorker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWorker(QObject *parent = nullptr);

    bool setSocketDescriptor(quintptr handle);

    void sendJson(const QJsonObject& jsonObject);

    const QString &username() const;
    void setUsername(const QString &newUsername);

    QString peerAddress() const;
    QString peerName() const;

    int id() const;
    void setId(int newId);

signals:
    void jsonReceived(const QJsonObject& jsonObject);
    void disconnectedFromClient();
    void errorOccurred();

    void logMessage(const QString& text);

public slots:
    void disconnectFromClient();

private:
    void receiveJson();

private:
    QTcpSocket* serverSocket_ = nullptr;
    QString username_;
    int id_ = -1;

};

#endif // SERVERWORKER_H
