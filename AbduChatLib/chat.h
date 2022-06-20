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

    const QString &date() const;
    void setDate(const QString &newDate);

    QJsonObject toJson() const;
    void toSqlRecord(QSqlRecord* record) const;
    static Chat fromJson(const QJsonObject& json);
    static Chat fromSqlRecord(const QSqlRecord& record);


private:
    int id_ = -1;
    QString type_;
    QString username_;
    QString date_;
};

#endif // CHAT_H
