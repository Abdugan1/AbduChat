#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include <QString>
#include <memory>

class QJsonObject;
class QSqlRecord;

class Chat;
using ChatPtr = std::shared_ptr<Chat>;

class Chat : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int chatId READ id WRITE setId RESET resetId NOTIFY idChanged)
    Q_PROPERTY(QString type READ type WRITE setType RESET resetType NOTIFY typeChanged)
    Q_PROPERTY(int user1Id READ user1Id WRITE setUser1Id RESET resetUser1Id NOTIFY user1IdChanged)
    Q_PROPERTY(int user2Id READ user2Id WRITE setUser2Id RESET resetUser2Id NOTIFY user2IdChanged)
    Q_PROPERTY(QString date READ date WRITE setDate RESET resetDate NOTIFY dateChanged)
public:
    explicit Chat();

    int id() const;
    void setId(int newId);
    void resetId();

    const QString &type() const;
    void setType(const QString &newType);
    void resetType();

    int user1Id() const;
    void setUser1Id(int newUser1Id);
    void resetUser1Id();

    int user2Id() const;
    void setUser2Id(int newUser2Id);
    void resetUser2Id();

    const QString &date() const;
    void setDate(const QString &newDate);
    void resetDate();

    QJsonObject toJson() const;
    void toSqlRecord(QSqlRecord* record) const;
    static ChatPtr fromJson(const QJsonObject& json);
    static ChatPtr fromSqlRecord(const QSqlRecord& record);

signals:
    void idChanged();
    void typeChanged();
    void user1IdChanged();
    void user2IdChanged();
    void dateChanged();

private:
    int id_ = -1;
    QString type_;
    int user1Id_ = -1;
    int user2Id_ = -1;
    QString date_;
};

#endif // CHAT_H
