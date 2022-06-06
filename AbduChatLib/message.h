#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>

class Message
{
public:
    explicit Message();

    int id() const;
    void setId(int newId);

    const QString &fromUser() const;
    void setFromUser(const QString &newFromUser);

    const QString &toUser() const;
    void setToUser(const QString &newToUser);

    const QString &text() const;
    void setText(const QString &newText);

    const QDateTime &sentDatetime() const;
    void setSentDatetime(const QDateTime &newSentDatetime);

private:
    int id_ = -1;
    QString fromUser_;
    QString toUser_;
    QString text_;
    QDateTime sentDatetime_;
};

#endif // MESSAGE_H
