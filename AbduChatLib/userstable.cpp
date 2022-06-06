#include "userstable.h"
#include "database_names.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDateTime>

#include <QDebug>

namespace FieldNames = db::users::fieldnames;
namespace FieldNums = db::users::fieldnums;

UsersTable::UsersTable(QObject *parent)
    : QSqlTableModel{parent}
{
    createTable();
    setTable(db::users::TableName);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

QVariant UsersTable::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> UsersTable::roleNames() const
{
    QHash<int, QByteArray> names;
    names[FieldNums::Id             + Qt::UserRole] = FieldNames::Id;
    names[FieldNums::Username       + Qt::UserRole] = FieldNames::Username;
    names[FieldNums::Password       + Qt::UserRole] = FieldNames::Password;
    names[FieldNums::InsertDatetime + Qt::UserRole] = FieldNames::InsertDatetime;
    return names;
}

bool UsersTable::hasUser(const QString &username, const QString &password)
{
    const QString execute("SELECT COUNT(*) FROM users WHERE username=:username AND password=:password;");
    QSqlQuery query;
    query.prepare(execute);
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.exec();
    query.next();
    return query.value(0).toBool();
}

bool UsersTable::insertUser(const QString &username, const QString &password)
{
    QSqlRecord newRecord = record();
    newRecord.setValue(FieldNames::Username, username);
    newRecord.setValue(FieldNames::Password, password);
    newRecord.setValue(FieldNames::InsertDatetime, QDateTime::currentDateTime().toString(Qt::ISODate));


    if (!insertRecord(rowCount(), newRecord))
        return false;

    if (!submitAll())
        return false;

    select();

    return true;
}

void UsersTable::createTable()
{
    if (QSqlDatabase::database().tables().contains(db::users::TableName))
        return;

    const QString execute = QString("CREATE TABLE IF NOT EXISTS %1 (" // TableName: users
                                    " '%2' INTEGER PRIMARY KEY," // id
                                    " '%3' TEXT NOT NULL UNIQUE," // username
                                    " '%4' TEXT NOT NULL," // password
                                    " '%5' TEXT NOT NULL" // insert_datetime
                                    ")")
            .arg(db::users::TableName)
            .arg(FieldNames::Id)
            .arg(FieldNames::Username)
            .arg(FieldNames::Password)
            .arg(FieldNames::InsertDatetime);

    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot create table '%s': %s",
               qPrintable(tableName()),
               qPrintable(query.lastError().text()));
    }
}
