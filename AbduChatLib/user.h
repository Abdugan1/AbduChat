#ifndef USER_H
#define USER_H

#include <QString>

class QJsonObject;
class QSqlRecord;

class User
{
public:
    explicit User();

    int id() const;
    void setId(int newId);

    const QString &firstName() const;
    void setFirstName(const QString &newFirstName);

    const QString &lastName() const;
    void setLastName(const QString &newLastName);

    const QString &username() const;
    void setUsername(const QString &newUsername);

    QJsonObject toJson() const;
    static User fromJson(const QJsonObject& json);
    static User fromSqlRecord(const QSqlRecord& record);

private:
    int id_ = -1;
    QString firstName_;
    QString lastName_;
    QString username_;
};

#endif // USER_H
