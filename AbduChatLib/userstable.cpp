#include "userstable.h"
#include "database_names.h"
#include "request_and_reply_constants.h"
#include "user.h"
#include "logger.h"

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

void UsersTable::addUser(const UserPtr &user)
{
    QSqlRecord userRecord = record();
    user->toSqlRecord(&userRecord);
    addUserRecord(userRecord);

    if (!submitAll()) {
        Logger::fatal("UsersTable::addUser::Submit all failed. id: "
                      + QString::number(user->id()) + " | reason: "
                      + lastError().text());
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
        Logger::fatal("UsersTable::addUserRecord::Insert record failed. id: "
                      + userRecord.value(FieldNames::Id).toString() + " | reason: "
                      + lastError().text());
    }
}

const QString &UsersTable::filterValue() const
{
    return filterValue_;
}

void UsersTable::setFilterValue(const QString &newFilterValue)
{
    if (filterValue_ == newFilterValue)
        return;
    if (newFilterValue.isEmpty())
        return resetFilterValue(); // void!

    filterValue_ = newFilterValue;

    const QString filterString = QString("first_name LIKE '%%1%' OR username LIKE '%%1%'").arg(filterValue_);
    setFilter(filterString);
    select();

    emit filterValueChanged();
}

void UsersTable::resetFilterValue()
{
    setFilterValue(" "); // forbidden symbol
}

QString UsersTable::getUsername(int userId) const
{
    const QString execute = "SELECT username FROM users WHERE id = :userId";
    QSqlQuery query;
    query.prepare(execute);
    query.bindValue(":userId", userId);
    if (!query.exec()) {
        Logger::fatal("UsersTable::getUsername::Get username failed. usersId: "
                      + QString::number(userId) + " | reason: "
                      + query.lastError().text());
    }
    query.next();
    return query.value(0).toString();
}
