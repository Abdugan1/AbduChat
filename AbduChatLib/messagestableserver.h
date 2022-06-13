#ifndef MESSAGESTABLESERVER_H
#define MESSAGESTABLESERVER_H

#include <QSqlTableModel>

class Message;

class MessagesTableServer : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit MessagesTableServer(QObject* parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

public slots:
    void insertMessage(const Message& message);

private:
    void createTable();
};

#endif // MESSAGESTABLESERVER_H
