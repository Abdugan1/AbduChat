#ifndef MESSAGESTABLE_H
#define MESSAGESTABLE_H

#include "sqltablemodel.h"
#include <memory>

class Message;
using MessagePtr = std::shared_ptr<Message>;

class MessagesTable : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(int currentChatId READ currentChatId WRITE setCurrentChatId NOTIFY currentChatIdChanged)
public:
    explicit MessagesTable(QObject* parent = nullptr);

    int currentChatId() const;
    void setCurrentChatId(int newCurrentChatId);

signals:
    void currentChatIdChanged();

private:
    void addMessage(const MessagePtr& message);

private:
    void createRoleNames();

    void addMessageRecord(const QSqlRecord& messageRecord);

private:
    int currentChatId_ = -1;

    friend class SqlDatabase;
};

#endif // MESSAGESTABLE_H
