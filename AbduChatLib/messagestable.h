#ifndef MESSAGESTABLECLIENT_H
#define MESSAGESTABLECLIENT_H

#include "sqltablemodel.h"

class Message;

class MessagesTable : public SqlTableModel
{
    Q_OBJECT
public:
    explicit MessagesTable(QObject* parent = nullptr);

private:
    void addMessage(const Message& message);

private:
    void createRoleNames();

    void addMessageRecord(const QSqlRecord& messageRecord);

    friend class SqlDatabase;
};

#endif // MESSAGESTABLECLIENT_H
