#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QString>
#include <QSharedPointer>

class User;
class Chat;
class Message;
using MessagePtr = QSharedPointer<Message>;

class QJsonObject;
class QSqlRecord;

class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId RESET resetId NOTIFY idChanged)
    Q_PROPERTY(User* from READ from WRITE setFrom RESET resetFrom NOTIFY fromChanged)
    Q_PROPERTY(Chat* chat READ chat WRITE setChat RESET resetChat NOTIFY chatChanged)
    Q_PROPERTY(QString text READ text WRITE setText RESET resetText NOTIFY textChanged)
    Q_PROPERTY(QString date READ date WRITE setDate RESET resetDate NOTIFY dateChanged)
public:
    explicit Message(QObject* parent = nullptr);

    int id() const;
    void setId(int newId);
    void resetId();

    User *from() const;
    void setFrom(User* newFrom);
    void resetFrom();

    Chat *chat() const;
    void setChat(Chat* newChat);
    void resetChat();

    const QString &text() const;
    void setText(const QString &newText);
    void resetText();

    const QString &date() const;
    void setDate(const QString &newDate);
    void resetDate();

    QJsonObject toJson() const;
    void toSqlRecord(QSqlRecord* record) const;
    static Message* fromJson(const QJsonObject& json);
    static Message* fromSqlRecord(const QSqlRecord& record);

signals:
    void idChanged();
    void fromChanged();
    void chatChanged();
    void textChanged();
    void dateChanged();

private:
    int id_ = -1;
    User* from_;
    Chat* chat_;
    QString text_;
    QString date_;
};

#endif // MESSAGE_H
