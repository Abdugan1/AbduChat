#ifndef CHATSTABLE_H
#define CHATSTABLE_H

#include "sqltablemodel.h"

class Chat;

class ChatsTable : public SqlTableModel
{
    Q_OBJECT
public:
    explicit ChatsTable(QObject *parent = nullptr);

protected:
    void addChat(const Chat& chat);

private:
    void createRoleNames();

    void addChatRecord(const QSqlRecord& chatRecord);

    friend class SqlDatabase;
};

#endif // CHATSTABLE_H
