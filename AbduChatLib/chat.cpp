#include "chat.h"
#include "request_and_reply_constants.h"
#include "database_names.h"

#include <QJsonObject>
#include <QSqlRecord>

Chat::Chat()
{

}

int Chat::id() const
{
    return id_;
}

void Chat::setId(int newId)
{
    id_ = newId;
}

const QString &Chat::type() const
{
    return type_;
}

void Chat::setType(const QString &newType)
{
    type_ = newType;
}

const QString &Chat::username() const
{
    return username_;
}

void Chat::setUsername(const QString &newUsername)
{
    username_ = newUsername;
}

const QString &Chat::date() const
{
    return date_;
}

void Chat::setDate(const QString &newDate)
{
    date_ = newDate;
}

QJsonObject Chat::toJson() const
{
    QJsonObject json;

    json[chat::headers::Id]         = id();
    json[chat::headers::Type]       = type();
    json[chat::headers::Username]   = username();
    json[chat::headers::Date]       = date();

    return json;
}

void Chat::toSqlRecord(QSqlRecord *record) const
{
    namespace FieldNames = db::chats::fieldnames;

    record->setValue(FieldNames::Id, id());
    record->setValue(FieldNames::Type, type());
    record->setValue(FieldNames::Username, username());
    record->setValue(FieldNames::Date, date());
}

Chat Chat::fromJson(const QJsonObject &json)
{
    Chat chat;

    chat.setId(json.value(chat::headers::Id).toInt());
    chat.setType(json.value(chat::headers::Type).toString());
    chat.setUsername(json.value(chat::headers::Username).toString());
    chat.setUsername(json.value(chat::headers::Date).toString());

    return chat;
}

Chat Chat::fromSqlRecord(const QSqlRecord &record)
{
    Chat chat;

    namespace FieldNames = db::chats::fieldnames;

    chat.setId(record.value(FieldNames::Id).toInt());
    chat.setType(record.value(FieldNames::Type).toString());
    chat.setUsername(record.value(chat::headers::Username).toString());
    chat.setDate(record.value(FieldNames::Date).toString());

    return chat;
}
