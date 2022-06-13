#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>

class QJsonObject;

class Message
{
public:
    explicit Message();

    int id() const;
    void setId(int newId);

    int fromUserId() const;
    void setFromUserId(int newFromUserId);

    int toUserId() const;
    void setToUserId(int newToUserId);

    const QString &text() const;
    void setText(const QString &newText);

    const QString &sentDatetime() const;
    void setSentDatetime(const QString &newSentDatetime);

private:
    int id_ = -1;
    int fromUserId_;
    int toUserId_;
    QString text_;
    QString sentDatetime_;
};

Message jsonToMessageSentDatetimeIsCurrentDatetime(const QJsonObject& jsonObject, int messageId = -1);
Message jsonToMessageSentDatetimeIsFromJsonObject(const QJsonObject& jsonObject, int messageId = -1);

#endif // MESSAGE_H
