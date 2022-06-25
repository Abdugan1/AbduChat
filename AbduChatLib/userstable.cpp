#include "userstable.h"
#include "database_names.h"
#include "request_and_reply_constants.h"
#include "user.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

namespace FieldNames = db::users::fieldnames;
namespace FieldNums = db::users::fieldnums;

UsersTable::UsersTable(QObject *parent)
    : SqlTableModel{parent}
{
    setTable(db::users::TableName);
    createRoleNames();
    select();
}

void UsersTable::addUser(const User &user)
{
    QSqlRecord userRecord = record();
    user.toSqlRecord(&userRecord);
    addUserRecord(userRecord);

    if (!submitAll()) {
        qFatal("Cannot submit user:\n id: %d\nusername: %s\nreason: %s",
               user.id(),
               qPrintable(user.username()),
               qPrintable(lastError().text())
               );
    }
}

void UsersTable::createRoleNames()
{
    QHash<int, QByteArray> names;
    names[FieldNums::Id         + Qt::UserRole] = qPrintable(FieldNames::Id);
    names[FieldNums::FirstName  + Qt::UserRole] = qPrintable(FieldNames::FirstName);
    names[FieldNums::LastName   + Qt::UserRole] = qPrintable(FieldNames::LastName);
    names[FieldNums::Username   + Qt::UserRole] = qPrintable(FieldNames::Username);
    names[FieldNums::Date       + Qt::UserRole] = qPrintable(FieldNames::Date);
    setRoleNames(names);
}

void UsersTable::addUserRecord(const QSqlRecord &userRecord)
{
    if (!insertRecord(rowCount(), userRecord)) {
        qFatal("Cannot submit user:\n id: %d\nusername: %s\nreason: %s",
               userRecord.value(FieldNames::Id).toInt(),
               qPrintable(userRecord.value(FieldNames::Username).toString()),
               qPrintable(lastError().text())
               );
    }
}
