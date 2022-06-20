#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

#include "user.h"
#include "chat.h"

class QJsonObject;
class QSqlRecord;

class Message
{
public:
    explicit Message();

    int id() const;
    void setId(int newId);

    const User &from() const;
    void setFrom(const User &newFrom);

    const Chat &chat() const;
    void setChat(const Chat &newChat);

    const QString &text() const;
    void setText(const QString &newText);

    const QString &date() const;
    void setDate(const QString &newDate);

    QJsonObject toJson() const;
    void toSqlRecord(QSqlRecord* record) const;
    static Message fromJson(const QJsonObject& json);
    static Message fromSqlRecord(const QSqlRecord& record);

private:
    int id_ = -1;
    User from_;
    Chat chat_;
    QString text_;
    QString date_;
};

#endif // MESSAGE_H
