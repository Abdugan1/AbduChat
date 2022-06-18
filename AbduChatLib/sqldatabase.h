#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <QObject>
#include <QSqlDatabase>

class SqlDatabase : public QObject, public QSqlDatabase
{
    Q_OBJECT
public:
    explicit SqlDatabase();

private:
    void connectToDatabase();

    void createTables();
    void createUsersTable();
    void createChatsTable();
    void createChatParticipantsTable();
    void createMessagesTable();

#ifdef ABDUCHAT_CLIENT
    void createChatsView();
#endif

#ifdef ABDUCHAT_SERVER
    void createUsersServerTable();
#endif
};

#endif // SQLDATABASE_H
