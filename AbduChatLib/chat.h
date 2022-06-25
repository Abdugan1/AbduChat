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

    int user1Id() const;
    void setUser1Id(int newUser1Id);

    int user2Id() const;
    void setUser2Id(int newUser2Id);

    const QString &date() const;
    void setDate(const QString &newDate);

    QJsonObject toJson() const;
    void toSqlRecord(QSqlRecord* record) const;
    static Chat fromJson(const QJsonObject& json);
    static Chat fromSqlRecord(const QSqlRecord& record);

private:
    int id_ = -1;
    QString type_;
    int user1Id_ = -1;
    int user2Id_ = -1;
    QString date_;
};

#endif // CHAT_H
