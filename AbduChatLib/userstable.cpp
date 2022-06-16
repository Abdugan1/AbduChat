#include "userstable.h"
#include "database_names.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDateTime>

#include <QDebug>

namespace FieldNames = db::users_server::fieldnames;
namespace FieldNums = db::users_server::fieldnums;

UsersServerTable::UsersServerTable(QObject *parent)
    : QSqlTableModel{parent}
{
    createTable();
    setTable(db::users_server::TableName);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

QVariant UsersServerTable::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> UsersServerTable::roleNames() const
{
    QHash<int, QByteArray> names;
    names[FieldNums::Id       + Qt::UserRole] = FieldNames::Id;
    names[FieldNums::Username + Qt::UserRole] = FieldNames::Username;
    names[FieldNums::Password + Qt::UserRole] = FieldNames::Password;
    return names;
}

bool UsersServerTable::hasUser(const QString &username, const QString &password)
{
    const QString execute = QString("SELECT COUNT(*) FROM %1 WHERE %2=:username AND %3=:password;")
                            .arg(db::users_server::TableName)
                            .arg(db::users::fieldnames::Username)
                            .arg(db::users_server::fieldnames::Password);
    QSqlQuery query;
    query.prepare(execute);
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.exec();
    query.next();
    return query.value(0).toBool();
}

bool UsersServerTable::insertUser(const QString &username, const QString &password)
{
    QSqlRecord newRecord = record();
    newRecord.setValue(FieldNames::Username, username);
    newRecord.setValue(FieldNames::Password, password);


    if (!insertRecord(rowCount(), newRecord))
        return false;

    if (!submitAll())
        return false;

    select();

    return true;
}

QSqlRecord UsersServerTable::getUser(const QString &username) const
{
    const QString execute = QString("SELECT * FROM %1 WHERE %2=:username")
                            .arg(db::users_server::TableName)
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

void UsersServerTable::createTable()
{
    if (QSqlDatabase::database().tables().contains(db::users::TableName))
        return;

//    const QString execute = QString("CREATE TABLE IF NOT EXISTS %1 (" // TableName: users
//                                    " '%2' INTEGER PRIMARY KEY," // id
//                                    " '%3' TEXT NOT NULL UNIQUE," // username
//                                    " '%4' TEXT NOT NULL," // password
//                                    " '%5' TEXT NOT NULL" // insert_datetime
//                                    ")")
//            .arg(db::users::TableName)
//            .arg(FieldNames::Id)
//            .arg(FieldNames::Username)
//            .arg(FieldNames::Password)
//            .arg(FieldNames::InsertDatetime);

//    QSqlQuery query;
//    if (!query.exec(execute)) {
//        qFatal("Cannot create table '%s': %s",
//               qPrintable(tableName()),
//               qPrintable(query.lastError().text()));
//    }
}
