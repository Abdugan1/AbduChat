#ifndef SQLDATABASECLIENT_H
#define SQLDATABASECLIENT_H

#include "sqldatabase.h"

class ChatsViewTable;

class SqlDatabaseClient : public SqlDatabase
{
    Q_OBJECT
public:
    ChatsViewTable *chatsViewTable() const;

    static SqlDatabaseClient& instance();

    void addUsers(const QJsonArray& users);
    void addMessages(const QJsonArray& messages);

    void addMessage(const MessagePtr& message);

    Q_INVOKABLE void setCurrentChat(int chatId);
    Q_INVOKABLE void setCurrentChat(int user1Id, int user2Id);

private:
    explicit SqlDatabaseClient(QObject *parent = nullptr);

    void createClientTables();
    void createChatsViewTable();

    void initClientTables();

private:
    ChatsViewTable* chatsViewTable_ = nullptr;
};

#endif // SQLDATABASECLIENT_H
