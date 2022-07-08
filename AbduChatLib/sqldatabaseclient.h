#ifndef SQLDATABASECLIENT_H
#define SQLDATABASECLIENT_H

#include "sqldatabase.h"

class ChatsViewTable;

class SqlDatabaseClient : public SqlDatabase
{
    Q_OBJECT
public:
    explicit SqlDatabaseClient(QObject *parent = nullptr);
    ChatsViewTable *chatsViewTable() const;

    void addUsers(const QJsonArray& users);
    void addMessages(const QJsonArray& messages);

    void addMessage(const MessagePtr& message);

    Q_INVOKABLE void setCurrentChat(int chatId);
    Q_INVOKABLE void setCurrentChat(int user1Id, int user2Id);

private:
    void createClientTables();
    void createChatsViewTable();

    void initClientTables();

private:
    ChatsViewTable* chatsViewTable_ = nullptr;
};

#endif // SQLDATABASECLIENT_H
