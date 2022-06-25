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

int Chat::user1Id() const
{
    return user1Id_;
}

void Chat::setUser1Id(int newUser1Id)
{
    user1Id_ = newUser1Id;
}

int Chat::user2Id() const
{
    return user2Id_;
}

void Chat::setUser2Id(int newUser2Id)
{
    user2Id_ = newUser2Id;
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
    json[chat::headers::User1Id]    = user1Id();
    json[chat::headers::User2Id]    = user2Id();
    json[chat::headers::Date]       = date();

    return json;
}

void Chat::toSqlRecord(QSqlRecord *record) const
{
    namespace FieldNames = db::chats::fieldnames;

    if (id() != -1)
        record->setValue(FieldNames::Id, id());

    record->setValue(FieldNames::Type, type());
    record->setValue(FieldNames::User1Id, user1Id());
    record->setValue(FieldNames::User2Id, user2Id());
    record->setValue(FieldNames::Date, date());
}

Chat Chat::fromJson(const QJsonObject &json)
{
    Chat chat;

    chat.setId(json.value(chat::headers::Id).toInt());
    chat.setType(json.value(chat::headers::Type).toString());
    chat.setUser1Id(json.value(chat::headers::User1Id).toInt());
    chat.setUser2Id(json.value(chat::headers::User2Id).toInt());
    chat.setDate(json.value(chat::headers::Date).toString());

    return chat;
}

Chat Chat::fromSqlRecord(const QSqlRecord &record)
{
    Chat chat;

    namespace FieldNames = db::chats::fieldnames;

    chat.setId(record.value(FieldNames::Id).toInt());
    chat.setType(record.value(FieldNames::Type).toString());
    chat.setUser1Id(record.value(chat::headers::User1Id).toInt());
    chat.setUser2Id(record.value(chat::headers::User2Id).toInt());
    chat.setDate(record.value(FieldNames::Date).toString());

    return chat;
}
