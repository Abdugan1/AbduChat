#include "usersservertable.h"
#include "database_names.h"
#include "user.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDateTime>

#include <QDebug>

namespace FieldNames = db::users_server::fieldnames;
namespace FieldNums = db::users_server::fieldnums;

UsersServerTable::UsersServerTable(QObject *parent)
    : SqlTableModel{parent}
{
    setTable(db::users_server::TableName);
    createRoleNames();
    select();
}

bool UsersServerTable::hasUser(const QString &username, const QString &password)
{

    const QString execute = QString("SELECT COUNT(*) FROM " + db::users_server::TableName +
                                    " WHERE " + FieldNames::Username + " =:username AND " +
                                    FieldNames::Password + " =:password;");
    QSqlQuery query;
    query.prepare(execute);
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.exec();
    query.next();
    return query.value(0).toBool();
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

bool UsersServerTable::addUser(const User &user, const QString &password)
{
    QSqlRecord userRecord = record();
    userRecord.setValue(FieldNames::Username, user.username());
    userRecord.setValue(FieldNames::Password, password);

    if (!addUserRecord(userRecord))
        return false;

    if (!submitAll())
        return false;

    return true;
}

void UsersServerTable::createRoleNames()
{
    QHash<int, QByteArray> names;
    names[FieldNums::Id       + Qt::UserRole] = qPrintable(FieldNames::Id);
    names[FieldNums::Username + Qt::UserRole] = qPrintable(FieldNames::Username);
    names[FieldNums::Password + Qt::UserRole] = qPrintable(FieldNames::Password);
    setRoleNames(names);
}

bool UsersServerTable::addUserRecord(const QSqlRecord &userRecord)
{
    return insertRecord(rowCount(), userRecord);
}
