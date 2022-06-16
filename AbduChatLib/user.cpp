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

QJsonObject User::toJson() const
{
    QJsonObject json;

    json[user::headers::Id]         = id();
    json[user::headers::FirstName]  = firstName();
    json[user::headers::LastName]   = lastName();
    json[user::headers::Username]   = username();

    return json;
}

User User::fromJson(const QJsonObject &json)
{
    User user;

    user.setId(json.value(user::headers::Id).toInt());
    user.setFirstName(json.value(user::headers::FirstName).toString());
    user.setLastName(json.value(user::headers::LastName).toString());
    user.setUsername(json.value(user::headers::Username).toString());

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

    return user;
}
