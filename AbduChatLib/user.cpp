#include "user.h"
#include "request_and_reply_constants.h"
#include "database_names.h"

#include <QJsonObject>
#include <QSqlRecord>

User::User(QObject *parent)
    : QObject(parent)
{

}

int User::id() const
{
    return id_;
}

void User::setId(int newId)
{
    if (id_ == newId)
        return;
    id_ = newId;
    emit idChanged();
}

void User::resetId()
{
    setId(-1); // TODO: Adapt to use your actual default value
}

const QString &User::firstName() const
{
    return firstName_;
}

void User::setFirstName(const QString &newFirstName)
{
    if (firstName_ == newFirstName)
        return;
    firstName_ = newFirstName;
    emit firstNameChanged();
}

void User::resetFirstName()
{
    setFirstName({}); // TODO: Adapt to use your actual default value
}

const QString &User::lastName() const
{
    return lastName_;
}

void User::setLastName(const QString &newLastName)
{
    if (lastName_ == newLastName)
        return;
    lastName_ = newLastName;
    emit lastNameChanged();
}

void User::resetLastName()
{
    setLastName({}); // TODO: Adapt to use your actual default value
}

const QString &User::username() const
{
    return username_;
}

void User::setUsername(const QString &newUsername)
{
    if (username_ == newUsername)
        return;
    username_ = newUsername;
    emit usernameChanged();
}

void User::resetUsername()
{
    setUsername({}); // TODO: Adapt to use your actual default value
}

const QString &User::date() const
{
    return date_;
}

void User::setDate(const QString &newDate)
{
    if (date_ == newDate)
        return;
    date_ = newDate;
    emit dateChanged();
}

void User::resetDate()
{
    setDate({}); // TODO: Adapt to use your actual default value
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

    if (id() != -1)
        record->setValue(FieldNames::Id, id());

    record->setValue(FieldNames::FirstName, firstName());
    record->setValue(FieldNames::LastName, lastName());
    record->setValue(FieldNames::Username, username());
    record->setValue(FieldNames::Date, date());
}

UserPtr User::fromJson(const QJsonObject &json)
{
    UserPtr user(new User);

    user->setId(json.value(user::headers::Id).toInt());
    user->setFirstName(json.value(user::headers::FirstName).toString());
    user->setLastName(json.value(user::headers::LastName).toString());
    user->setUsername(json.value(user::headers::Username).toString());
    user->setDate(json.value(user::headers::Date).toString());

    return user;
}

UserPtr User::fromSqlRecord(const QSqlRecord &record)
{
    UserPtr user(new User);

    namespace FieldNames = db::users::fieldnames;

    user->setId(record.value(FieldNames::Id).toInt());
    user->setFirstName(record.value(FieldNames::FirstName).toString());
    user->setLastName(record.value(FieldNames::LastName).toString());
    user->setUsername(record.value(FieldNames::Username).toString());
    user->setDate(record.value(FieldNames::Date).toString());

    return user;
}

bool operator==(const User& left, const User& right)
{
    return left.id_ == right.id_;
}
