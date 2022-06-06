#include "message.h"

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

const QString &Message::fromUser() const
{
    return fromUser_;
}

void Message::setFromUser(const QString &newFromUser)
{
    fromUser_ = newFromUser;
}

const QString &Message::toUser() const
{
    return toUser_;
}

void Message::setToUser(const QString &newToUser)
{
    toUser_ = newToUser;
}

const QString &Message::text() const
{
    return text_;
}

void Message::setText(const QString &newText)
{
    text_ = newText;
}

const QDateTime &Message::sentDatetime() const
{
    return sentDatetime_;
}

void Message::setSentDatetime(const QDateTime &newSentDatetime)
{
    sentDatetime_ = newSentDatetime;
}
