#include "chat.h"
#include "request_and_reply_constants.h"
#include "database_names.h"

#include <QJsonObject>
#include <QSqlRecord>

Chat::Chat(QObject *parent)
    : QObject(parent)
{

}

Chat::~Chat()
{
    qDebug() << "Chat::Destructor";
}

int Chat::id() const
{
    return id_;
}

void Chat::setId(int newId)
{
    if (id_ == newId)
        return;
    id_ = newId;
    emit idChanged();
}

void Chat::resetId()
{
    setId(-1); // TODO: Adapt to use your actual default value
}

const QString &Chat::type() const
{
    return type_;
}

void Chat::setType(const QString &newType)
{
    if (type_ == newType)
        return;
    type_ = newType;
    emit typeChanged();
}

void Chat::resetType()
{
    setType({}); // TODO: Adapt to use your actual default value
}

int Chat::user1Id() const
{
    return user1Id_;
}

void Chat::setUser1Id(int newUser1Id)
{
    if (user1Id_ == newUser1Id)
        return;
    user1Id_ = newUser1Id;
    emit user1IdChanged();
}

void Chat::resetUser1Id()
{
    setUser1Id({}); // TODO: Adapt to use your actual default value
}

int Chat::user2Id() const
{
    return user2Id_;
}

void Chat::setUser2Id(int newUser2Id)
{
    if (user2Id_ == newUser2Id)
        return;
    user2Id_ = newUser2Id;
    emit user2IdChanged();
}

void Chat::resetUser2Id()
{
    setUser2Id({}); // TODO: Adapt to use your actual default value
}

const QString &Chat::date() const
{
    return date_;
}

void Chat::setDate(const QString &newDate)
{
    if (date_ == newDate)
        return;
    date_ = newDate;
    emit dateChanged();
}

void Chat::resetDate()
{
    setDate({}); // TODO: Adapt to use your actual default value
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

ChatPtr Chat::fromJson(const QJsonObject &json)
{
    ChatPtr chat(new Chat);

    chat->setId(json.value(chat::headers::Id).toInt());
    chat->setType(json.value(chat::headers::Type).toString());
    chat->setUser1Id(json.value(chat::headers::User1Id).toInt());
    chat->setUser2Id(json.value(chat::headers::User2Id).toInt());
    chat->setDate(json.value(chat::headers::Date).toString());

    return chat;
}

ChatPtr Chat::fromSqlRecord(const QSqlRecord &record)
{
    ChatPtr chat(new Chat);

    namespace FieldNames = db::chats::fieldnames;

    chat->setId(record.value(FieldNames::Id).toInt());
    chat->setType(record.value(FieldNames::Type).toString());
    chat->setUser1Id(record.value(chat::headers::User1Id).toInt());
    chat->setUser2Id(record.value(chat::headers::User2Id).toInt());
    chat->setDate(record.value(FieldNames::Date).toString());

    return chat;
}
