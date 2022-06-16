#ifndef CHAT_H
#define CHAT_H

#include <QString>

class QJsonObject;
class QSqlRecord;

class Chat
{
public:
    explicit Chat();

    int id() const;
    void setId(int newId);

    const QString &type() const;
    void setType(const QString &newType);

    /// Kind of title. Every chats title is like username
    const QString &username() const;
    void setUsername(const QString &newUsername);

    QJsonObject toJson() const;
    static Chat fromJson(const QJsonObject& json);
    static Chat fromSqlRecord(const QSqlRecord& record);

private:
    int id_ = -1;
    QString type_;
    QString username_;
};

#endif // CHAT_H
