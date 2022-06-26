#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QString>
#include <memory>

class User;
class Chat;
class Message;
using UserPtr = std::shared_ptr<User>;
using ChatPtr = std::shared_ptr<Chat>;
using MessagePtr = std::shared_ptr<Message>;

class QJsonObject;
class QSqlRecord;

class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId RESET resetId NOTIFY idChanged)
    Q_PROPERTY(UserPtr from READ from WRITE setFrom RESET resetFrom NOTIFY fromChanged)
    Q_PROPERTY(ChatPtr chat READ chat WRITE setChat RESET resetChat NOTIFY chatChanged)
    Q_PROPERTY(QString text READ text WRITE setText RESET resetText NOTIFY textChanged)
    Q_PROPERTY(QString date READ date WRITE setDate RESET resetDate NOTIFY dateChanged)
public:
    explicit Message();

    int id() const;
    void setId(int newId);
    void resetId();

    const UserPtr &from() const;
    void setFrom(const UserPtr &newFrom);
    void resetFrom();

    const ChatPtr &chat() const;
    void setChat(const ChatPtr &newChat);
    void resetChat();

    const QString &text() const;
    void setText(const QString &newText);
    void resetText();

    const QString &date() const;
    void setDate(const QString &newDate);
    void resetDate();

    QJsonObject toJson() const;
    void toSqlRecord(QSqlRecord* record) const;
    static MessagePtr fromJson(const QJsonObject& json);
    static MessagePtr fromSqlRecord(const QSqlRecord& record);

signals:
    void idChanged();
    void fromChanged();
    void chatChanged();
    void textChanged();
    void dateChanged();

private:
    int id_ = -1;
    UserPtr from_;
    ChatPtr chat_;
    QString text_;
    QString date_;
};

#endif // MESSAGE_H
