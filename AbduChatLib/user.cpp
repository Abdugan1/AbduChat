#include "user.h"
#include "request_and_reply_constants.h"
#include "database_names.h"

#include <QJsonObject>
#include <QSqlRecord>

User::User()
{

}

int User::id() const
{
    return id_;
}

void User::setId(int newId)
{
    id_ = newId;
}

const QString &User::firstName() const
{
    return firstName_;
}

void User::setFirstName(const QString &newFirstName)
{
    firstName_ = newFirstName;
}

const QString &User::lastName() const
{
    return lastName_;
}

void User::setLastName(const QString &newLastName)
{
    lastName_ = newLastName;
}

const QString &User::username() const
{
    return username_;
}

void User::setUsername(const QString &newUsername)
{
    username_ = newUsername;
}

const QString &User::date() const
{
    return date_;
}

void User::setDate(const QString &newDate)
{
    date_ = newDate;
}

bool User::isValid() const
{
    return id() != -1;
}

QJsonObject User::toJson() const
{
    QJsonObject json;

    json[user::headers::Id]         = id();
    json[user::headers::FirstName]  = firstName();
    json[user::headers::LastName]   = lastName();
    json[user::headers::Username]   = username();
    json[user::headers::Date]       = date();

    return json;
}

void User::toSqlRecord(QSqlRecord *record) const
{
    namespace FieldNames = db::users::fieldnames;

    record->setValue(FieldNames::Id, id());
    record->setValue(FieldNames::FirstName, firstName());
    record->setValue(FieldNames::LastName, lastName());
    record->setValue(FieldNames::Username, username());
    record->setValue(FieldNames::Date, date());
}

User User::fromJson(const QJsonObject &json)
{
    User user;

    user.setId(json.value(user::headers::Id).toInt());
    user.setFirstName(json.value(user::headers::FirstName).toString());
    user.setLastName(json.value(user::headers::LastName).toString());
    user.setUsername(json.value(user::headers::Username).toString());
    user.setDate(json.value(user::headers::Date).toString());

    return user;
}

User User::fromSqlRecord(const QSqlRecord &record)
{
    User user;

    namespace FieldNames = db::users::fieldnames;

    user.setId(record.value(FieldNames::Id).toInt());
    user.setFirstName(record.value(FieldNames::FirstName).toString());
    user.setLastName(record.value(FieldNames::LastName).toString());
    user.setUsername(record.value(FieldNames::Username).toString());
    user.setUsername(record.value(FieldNames::Date).toString());

    return user;
}

bool operator==(const User& left, const User& right)
{
    return left.id_ == right.id_;
}
