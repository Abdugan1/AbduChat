#include "message.h"
#include "user.h"
#include "chat.h"
#include "request_and_reply_constants.h"
#include "database_names.h"

#include <QJsonObject>
#include <QSqlRecord>

Message::Message(QObject *parent)
    : QObject(parent)
{

}

int Message::id() const
{
    return id_;
}

void Message::setId(int newId)
{
    if (id_ == newId)
        return;
    id_ = newId;
    emit idChanged();
}

void Message::resetId()
{
    setId(-1); // TODO: Adapt to use your actual default value
}

User *Message::from() const
{
    return from_;
}

void Message::setFrom(User *newFrom)
{
    if (from_ == newFrom)
        return;
    from_ = newFrom;
    emit fromChanged();
}

void Message::resetFrom()
{
    setFrom({}); // TODO: Adapt to use your actual default value
}

Chat *Message::chat() const
{
    return chat_;
}

void Message::setChat(Chat *newChat)
{
    if (chat_ == newChat)
        return;
    chat_ = newChat;
    emit chatChanged();
}

void Message::resetChat()
{
    setChat({}); // TODO: Adapt to use your actual default value
}

const QString &Message::text() const
{
    return text_;
}

void Message::setText(const QString &newText)
{
    if (text_ == newText)
        return;
    text_ = newText;
    emit textChanged();
}

void Message::resetText()
{
    setText({}); // TODO: Adapt to use your actual default value
}

const QString &Message::date() const
{
    return date_;
}

void Message::setDate(const QString &newDate)
{
    if (date_ == newDate)
        return;
    date_ = newDate;
    emit dateChanged();
}

void Message::resetDate()
{
    setDate({}); // TODO: Adapt to use your actual default value
}

QJsonObject Message::toJson() const
{
    QJsonObject json;

    json[message::headers::Id]   = id();
    json[message::headers::From] = from()->toJson();
    json[message::headers::Chat] = chat()->toJson();
    json[message::headers::Text] = text();
    json[message::headers::Date] = date();

    return json;
}

void Message::toSqlRecord(QSqlRecord *record) const
{
    namespace FieldNames = db::messages::fieldnames;

    if (id() != -1)
        record->setValue(FieldNames::Id, id());

    record->setValue(FieldNames::FromUserId, from()->id());
    record->setValue(FieldNames::ChatId, chat()->id());
    record->setValue(FieldNames::Text, text());
    record->setValue(FieldNames::Date, date());
}

Message* Message::fromJson(const QJsonObject &json)
{
    Message* message(new Message);

    message->setId(json.value(message::headers::Id).toInt());
    message->setFrom(User::fromJson(json.value(message::headers::From).toObject()));
    message->setChat(Chat::fromJson(json.value(message::headers::Chat).toObject()));
    message->setText(json.value(message::headers::Text).toString());
    message->setDate(json.value(message::headers::Date).toString());

    return message;
}

Message* Message::fromSqlRecord(const QSqlRecord &record)
{
    Message* message(new Message);

    namespace FieldNames = db::messages::fieldnames;

    message->setId(record.value(FieldNames::Id).toInt());
    message->setFrom(User::fromSqlRecord(record));
    message->setChat(Chat::fromSqlRecord(record));
    message->setText(record.value(FieldNames::Text).toString());
    message->setDate(record.value(FieldNames::Date).toString());

    return message;
}
