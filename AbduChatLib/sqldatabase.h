#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>

class User;
class Chat;
class Message;


class UsersTable;
class ChatsTable;
class MessagesTable;

class UsersServerTable;
class ServerLogsTable;

class SqlDatabase : public QObject, public QSqlDatabase
{
    Q_OBJECT
    Q_PROPERTY(UsersTable *usersTable READ usersTable CONSTANT)
    Q_PROPERTY(ChatsTable *chatsTable READ chatsTable CONSTANT)
    Q_PROPERTY(MessagesTable *messagesTable READ messagesTable CONSTANT)
    Q_PROPERTY(UsersServerTable *userServerTable READ userServerTable CONSTANT)
    Q_PROPERTY(ServerLogsTable *serverLogsTable READ serverLogsTable CONSTANT)
public:
    explicit SqlDatabase(QObject* parent = nullptr);

    UsersTable *usersTable() const;
    ChatsTable *chatsTable() const;
    MessagesTable *messagesTable() const;

    UsersServerTable *userServerTable() const;
    ServerLogsTable *serverLogsTable() const;

    void addUser(const User& user);

#ifdef ABDUCHAT_SERVER
    bool addUser(const User& user, const QString& password);
#endif

    void addChat(const Chat& chat);

    void addMessage(const Message& message);


private:
    void connectToDatabase();

    void createTables();
    void createUsersTable();
    void createChatsTable();
    void createChatParticipantsTable();
    void createMessagesTable();

    void initTables();

#ifdef ABDUCHAT_CLIENT
    void createChatsView();
#endif

#ifdef ABDUCHAT_SERVER
    void createServerLogsTable();
    void createUsersServerTable();
#endif

private:
    UsersTable* usersTable_ = nullptr;
    ChatsTable* chatsTable_ = nullptr;
    MessagesTable* messagesTable_ = nullptr;

    UsersServerTable* userServerTable_ = nullptr;
    ServerLogsTable* serverLogsTable_ = nullptr;
};

#endif // SQLDATABASE_H
