#ifndef MESSAGESTABLE_H
#define MESSAGESTABLE_H

#include <QSqlTableModel>

class Message;

class MessagesTable : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit MessagesTable(QObject* parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

public slots:
    void insertMessage(const Message& message);

private:
    void createTable();
};

#endif // MESSAGESTABLE_H
