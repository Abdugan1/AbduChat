#ifndef MESSAGESTABLECLIENT_H
#define MESSAGESTABLECLIENT_H

#include <QSqlTableModel>

class Message;

class MessagesTableClient : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(int recipientId READ recipientId WRITE setRecipientId NOTIFY recipientIdChanged)
    Q_PROPERTY(int myId READ myId WRITE setMyId NOTIFY myIdChanged)
public:
    explicit MessagesTableClient(QObject* parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    int recipientId() const;
    void setRecipientId(int id);

    int myId() const;
    void setMyId(int id);

signals:
    void recipientIdChanged();

    void myIdChanged();

public slots:
    void insertMessages(const QJsonArray& messages);
    void insertMessage(const Message& message);    

private:
    void insertMessageWithoutSubmit(const Message& message);

    void createTable();

private:
    int recipientId_ = -1;
    int myId_ = -1;
};

#endif // MESSAGESTABLECLIENT_H
