#ifndef SQLDATABASESERVER_H
#define SQLDATABASESERVER_H

#include "sqldatabase.h"

class UsersServerTable;
class ServerLogsTable;

class SqlDatabaseServer : public SqlDatabase
{
    Q_OBJECT
public:
    explicit SqlDatabaseServer(QObject* parent = nullptr);

    UsersServerTable *usersServerTable() const;
    ServerLogsTable *serverLogsTable() const;

    bool addUser(const User& user, const QString& password);

    QSqlRecord getUser(const QString& username) const;

private:
    void createServerTables();
    void createUsersServerTable();
    void createServerLogsTable();

    void initServerTables();

private:
    UsersServerTable* usersServerTable_ = nullptr;
    ServerLogsTable*  serverLogsTable_  = nullptr;
};

#endif // SQLDATABASESERVER_H
