#include "sqldatabaseserver.h"
#include "database_names.h"
#include "userstable.h"
#include "usersservertable.h"
#include "serverlogstable.h"

#include <QSqlQuery>
#include <QSqlRecord>
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

QSqlRecord SqlDatabaseServer::getUser(const QString &username) const
{
    const QString execute = QString("SELECT * FROM %1 WHERE %2=:username")
                            .arg(db::users::TableName)
                            .arg(db::users::fieldnames::Username);
    QSqlQuery query;
    query.prepare(execute);
    query.bindValue(":username", username);
    if (!query.exec()) {
        qFatal("Cannot get user %s: %s", qPrintable(username), qPrintable(query.lastError().text()));
    }
    query.next();
    return query.record();
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
                                        Username + " TEXT," +
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
