#include "sqldatabaseserver.h"
#include "database_names.h"
#include "usersservertable.h"
#include "serverlogstable.h"

#include <QSqlQuery>
#include <QSqlError>

SqlDatabaseServer::SqlDatabaseServer(QObject *parent)
    : SqlDatabase(parent)
{
    createServerTables();
    initServerTables();
}

UsersServerTable *SqlDatabaseServer::usersServerTable() const
{
    return usersServerTable_;
}

ServerLogsTable *SqlDatabaseServer::serverLogsTable() const
{
    return serverLogsTable_;
}

bool SqlDatabaseServer::addUser(const User &user, const QString &password)
{
    SqlDatabase::addUser(user);
    return usersServerTable_->addUser(user, password);
}

void SqlDatabaseServer::createServerTables()
{
    createUsersServerTable();
    createServerLogsTable();
}

void SqlDatabaseServer::createUsersServerTable()
{
    using namespace db::users_server;
    using namespace fieldnames;
    const QString execute = QString("CREATE TABLE IF NOT EXISTS " + TableName + "(" +
                                        Id + " INTEGER PRIMARY KEY," +
                                        Password + " TEXT,"
                                    "   FOREIGN KEY(" + Id + ") REFERENCES " + db::users::TableName + "(" + db::users::fieldnames::Id + ")"
                                    ");"
                                    );
    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot create table %s: %s\n"
               "executed: %s",
               qPrintable(TableName), qPrintable(query.lastError().text()), qPrintable(query.executedQuery()));
    }
}

void SqlDatabaseServer::createServerLogsTable()
{
    using namespace db::server_logs;
    using namespace fieldnames;
    const QString execute = QString("CREATE TABLE IF NOT EXISTS " + TableName + "(" +
                                        Id + " INTEGER PRIMARY KEY," +
                                        Text + " TEXT," +
                                        Date + " TEXT"
                                               ");"
                                    );
    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot create table %s: %s",
               qPrintable(TableName), qPrintable(query.lastError().text()));
    }
}

void SqlDatabaseServer::initServerTables()
{
    usersServerTable_ = new UsersServerTable(this);
    serverLogsTable_  = new ServerLogsTable(this);
}
