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

    const QString &date() const;
    void setDate(const QString &newDate);

    bool isValid() const;

    QJsonObject toJson() const;
    void  toSqlRecord(QSqlRecord* record) const;
    static User fromJson(const QJsonObject& json);
    static User fromSqlRecord(const QSqlRecord& record);

    friend bool operator==(const User& left, const User& right);

private:
    int id_ = -1;
    QString firstName_;
    QString lastName_;
    QString username_;
    QString date_;
};

#endif // USER_H
