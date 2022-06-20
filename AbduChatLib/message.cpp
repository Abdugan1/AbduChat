#include "message.h"
#include "request_and_reply_constants.h"
#include "database_names.h"

#include <QJsonObject>
#include <QSqlRecord>

Message::Message()
{

}

int Message::id() const
{
    return id_;
}

void Message::setId(int newId)
{
    id_ = newId;
}

const User &Message::from() const
{
    return from_;
}

void Message::setFrom(const User &newFrom)
{
    from_ = newFrom;
}

const Chat &Message::chat() const
{
    return chat_;
}

void Message::setChat(const Chat &newChat)
{
    chat_ = newChat;
}

const QString &Message::text() const
{
    return text_;
}

void Message::setText(const QString &newText)
{
    text_ = newText;
}

const QString &Message::date() const
{
    return date_;
}

void Message::setDate(const QString &newDate)
{
    date_ = newDate;
}

QJsonObject Message::toJson() const
{
    QJsonObject json;

    json[message::headers::Id]   = id();
    json[message::headers::From] = from().toJson();
    json[message::headers::Chat] = chat().toJson();
    json[message::headers::Text] = text();
    json[message::headers::Date] = date();

    return json;
}

void Message::toSqlRecord(QSqlRecord *record) const
{
    namespace FieldNames = db::messages::fieldnames;

    record->setValue(FieldNames::Id, id());
    record->setValue(FieldNames::FromUserId, from().id());
    record->setValue(FieldNames::ChatId, chat().id());
    record->setValue(FieldNames::Text, text());
    record->setValue(FieldNames::Date, date());
}

Message Message::fromJson(const QJsonObject &json)
{
    Message message;

    message.setId(json.value(message::headers::Id).toInt());
    message.setFrom(User::fromJson(json.value(message::headers::From).toObject()));
    message.setChat(Chat::fromJson(json.value(message::headers::Chat).toObject()));
    message.setText(json.value(message::headers::Text).toString());
    message.setDate(json.value(message::headers::Date).toString());

    return message;
}

Message Message::fromSqlRecord(const QSqlRecord &record)
{
    Message message;

    namespace FieldNames = db::messages::fieldnames;

    message.setId(record.value(FieldNames::Id).toInt());
    message.setFrom(User::fromSqlRecord(record));
    message.setChat(Chat::fromSqlRecord(record));
    message.setText(record.value(FieldNames::Text).toString());
    message.setDate(record.value(FieldNames::Date).toString());

    return message;
}
