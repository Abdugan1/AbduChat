#ifndef SQLDATABASECLIENT_H
#define SQLDATABASECLIENT_H

#include "sqldatabase.h"

class ChatsViewTable;

class SqlDatabaseClient : public SqlDatabase
{
    Q_OBJECT
public:
    explicit SqlDatabaseClient(QObject *parent = nullptr);

private:
    void createClientTables();
    void createChatsViewTable();

    void initClientTables();

private:
    ChatsViewTable* chatsViewTable_ = nullptr;
};

#endif // SQLDATABASECLIENT_H
