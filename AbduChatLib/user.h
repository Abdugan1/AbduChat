#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>
#include <memory>

class QJsonObject;
class QSqlRecord;

class User;
using UserPtr = std::shared_ptr<User>;

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId RESET resetId NOTIFY idChanged)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName RESET resetFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName RESET resetLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString username READ username WRITE setUsername RESET resetUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString date READ date WRITE setDate RESET resetDate NOTIFY dateChanged)
public:
    explicit User(QObject* parent = nullptr);

    int id() const;
    void setId(int newId);
    void resetId();

    const QString &firstName() const;
    void setFirstName(const QString &newFirstName);
    void resetFirstName();

    const QString &lastName() const;
    void setLastName(const QString &newLastName);
    void resetLastName();

    const QString &username() const;
    void setUsername(const QString &newUsername);
    void resetUsername();

    const QString &date() const;
    void setDate(const QString &newDate);
    void resetDate();

    bool isValid() const;

    QJsonObject toJson() const;
    void  toSqlRecord(QSqlRecord* record) const;
    static UserPtr fromJson(const QJsonObject& json);
    static UserPtr fromSqlRecord(const QSqlRecord& record);

    friend bool operator==(const User& left, const User& right);

signals:
    void idChanged();
    void firstNameChanged();
    void lastNameChanged();
    void usernameChanged();
    void dateChanged();

private:
    int id_ = -1;
    QString firstName_;
    QString lastName_;
    QString username_;
    QString date_;
};

#endif // USER_H
