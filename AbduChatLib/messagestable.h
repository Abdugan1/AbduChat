#ifndef MESSAGESTABLE_H
#define MESSAGESTABLE_H

#include "sqltablemodel.h"
#include <memory>

class Chat;
class Message;
using ChatPtr = std::shared_ptr<Chat>;
using MessagePtr = std::shared_ptr<Message>;

class QJSValue;

class MessagesTable : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(Chat* currentChat READ currentChat NOTIFY currentChatChanged)
public:
    explicit MessagesTable(QObject* parent = nullptr);

    Chat *currentChat() const;
    Q_INVOKABLE void setCurrentChat(const QJSValue& newCurrentChat);

signals:
    void currentChatChanged();

private:
    void addMessage(const MessagePtr& message);

private:
    void createRoleNames();

    void addMessageRecord(const QSqlRecord& messageRecord);

    void selectCurrentChatValues();

private:
    ChatPtr currentChat_ = nullptr;
    int currentChatId_ = -1;


    friend class SqlDatabase;
};

#endif // MESSAGESTABLE_H
