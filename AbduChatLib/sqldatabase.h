#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>

#include "user.h"
#include "chat.h"
#include "message.h"

class UsersTable;
class ChatsTable;
class MessagesTable;

class SqlDatabase : public QObject, public QSqlDatabase
{
    Q_OBJECT
//    Q_PROPERTY(UsersTable *usersTable READ usersTable CONSTANT)
//    Q_PROPERTY(ChatsTable *chatsTable READ chatsTable CONSTANT)
//    Q_PROPERTY(MessagesTable *messagesTable READ messagesTable CONSTANT)
public:
    explicit SqlDatabase(QObject* parent = nullptr);

    UsersTable *usersTable() const;
    ChatsTable *chatsTable() const;
    MessagesTable *messagesTable() const;

    void addUser(const UserPtr& user);

    void addChat(const ChatPtr& chat);

    void addMessage(const MessagePtr& message);

private:
    void connectToDatabase();

    void createTables();
    void createUsersTable();
    void createChatsTable();
    void createMessagesTable();

    void initTables();

private:
    UsersTable* usersTable_ = nullptr;
    ChatsTable* chatsTable_ = nullptr;
    MessagesTable* messagesTable_ = nullptr;
};

#endif // SQLDATABASE_H
