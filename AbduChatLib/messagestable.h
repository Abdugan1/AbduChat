#ifndef MESSAGESTABLE_H
#define MESSAGESTABLE_H

#include "sqltablemodel.h"
#include "chat.h"
#include "message.h"

class QJSValue;

class MessagesTable : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(Chat* currentChat READ currentChat NOTIFY currentChatChanged)
public:
    explicit MessagesTable(QObject* parent = nullptr);

    Chat *currentChat() const;

signals:
    void currentChatChanged();

private:
    void addMessage(const MessagePtr& message);

    void setCurrentChat(const ChatPtr& newCurrentChat);

private:
    void createRoleNames();

    void addMessageRecord(const QSqlRecord& messageRecord);

    void selectCurrentChatValues();

private:
    Chat* currentChat_ = nullptr;
    int currentChatId_ = -1;


    friend class SqlDatabase;
    friend class SqlDatabaseClient;
};

#endif // MESSAGESTABLE_H
