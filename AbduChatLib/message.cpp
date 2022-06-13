#include "message.h"
#include "request_and_reply_constants.h"

#include <QJsonObject>

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

int Message::fromUserId() const
{
    return fromUserId_;
}

void Message::setFromUserId(int newFromUserId)
{
    fromUserId_ = newFromUserId;
}

int Message::toUserId() const
{
    return toUserId_;
}

void Message::setToUserId(int newToUserId)
{
    toUserId_ = newToUserId;
}

const QString &Message::text() const
{
    return text_;
}

void Message::setText(const QString &newText)
{
    text_ = newText;
}

const QString &Message::sentDatetime() const
{
    return sentDatetime_;
}

void Message::setSentDatetime(const QString &newSentDatetime)
{
    sentDatetime_ = newSentDatetime;
}

Message jsonToMessageSentDatetimeIsCurrentDatetime(const QJsonObject& jsonObject, int messageId)
{
    const int fromUserId       = jsonObject.value(request::headers::FromUserId).toInt();
    const int toUserId         = jsonObject.value(request::headers::ToUserId).toInt();
    const QString text         = jsonObject.value(request::headers::Text).toString();
    const QString sentDatetime = QDateTime::currentDateTime().toString(Qt::ISODate);

    Message message;
    message.setId(messageId);
    message.setFromUserId(fromUserId);
    message.setToUserId(toUserId);
    message.setText(text);
    message.setSentDatetime(sentDatetime);

    return message;
}

Message jsonToMessageSentDatetimeIsFromJsonObject(const QJsonObject &jsonObject, int messageId)
{
    const int fromUserId        = jsonObject.value(request::headers::FromUserId).toInt();
    const int toUserId          = jsonObject.value(request::headers::ToUserId).toInt();
    const QString text          = jsonObject.value(request::headers::Text).toString();
    const QString sentDatetime  = jsonObject.value(request::headers::SentDatetime).toString();

    Message message;
    message.setId(messageId);
    message.setFromUserId(fromUserId);
    message.setToUserId(toUserId);
    message.setText(text);
    message.setSentDatetime(sentDatetime);

    return message;
}
