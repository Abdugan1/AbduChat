#include "sqldatabase.h"
#include "database_names.h"

#include "userstable.h"
#include "chatstable.h"
#include "messagestableclient.h"
#include "usersservertable.h"
#include "serverlogstable.h"

#include <QSqlQuery>
#include <QSqlError>

#include <QDir>
#include <QStandardPaths>

SqlDatabase::SqlDatabase(QObject *parent)
    : QObject(parent)
    , QSqlDatabase()
{
    connectToDatabase();
    createTables();
    initTables();
}

UsersTable *SqlDatabase::usersTable() const
{
    return usersTable_;
}

ChatsTable *SqlDatabase::chatsTable() const
{
    return chatsTable_;
}

MessagesTable *SqlDatabase::messagesTable() const
{
    return messagesTable_;
}

UsersServerTable *SqlDatabase::userServerTable() const
{
    return userServerTable_;
}

void SqlDatabase::addUser(const User &user)
{
    usersTable_->addUser(user);
}

#ifdef ABDUCHAT_SERVER
bool SqlDatabase::addUser(const User &user, const QString &password)
{
    usersTable_->addUser(user);
    return userServerTable_->addUser(user, password);
}
#endif

void SqlDatabase::addChat(const Chat &chat)
{
    chatsTable_->addChat(chat);
}

void SqlDatabase::addMessage(const Message &message)
{
    messagesTable_->addMessage(message);
}

void SqlDatabase::connectToDatabase()
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.isValid()) {
        database = QSqlDatabase::addDatabase("QSQLITE");
        if (!database.isValid())
            qFatal("Cannot add database: %s", qPrintable(database.lastError().text()));
    }

    const QDir writeDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (!writeDir.mkpath("."))
        qFatal("Failed to create writable directory at %s", qPrintable(writeDir.absolutePath()));

    // Ensure that we have a writable location on all devices.
    const QString fileName = writeDir.absolutePath() + "/AbduChat.sqlite3";
    // When using the SQLite driver, open() will create the SQLite database if it doesn't exist.
    database.setDatabaseName(fileName);
    if (!database.open()) {
        qFatal("Cannot open database: %s", qPrintable(database.lastError().text()));
        QFile::remove(fileName);
    }
}

void SqlDatabase::createTables()
{
    createUsersTable();
    createChatsTable();
    createChatParticipantsTable();
    createMessagesTable();

#ifdef ABDUCHAT_CLIENT
    createChatsView();
#endif

#ifdef ABDUCHAT_SERVER
    createServerLogsTable();
    createUsersServerTable();
#endif
}

void SqlDatabase::createUsersTable()
{
    using namespace db::users;
    using namespace fieldnames;
    const QString execute = QString("CREATE TABLE IF NOT EXISTS " + TableName + "(" +
                                        Id + " INTEGER PRIMARY KEY," +
                                        FirstName + " TEXT," +
                                        LastName + " TEXT," +
                                        Username + " TEXT"
                                    ");");

    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot create table %s: %s",
               qPrintable(TableName), qPrintable(query.lastError().text()));
    }
}

void SqlDatabase::createChatsTable()
{
    using namespace db::chats;
    using namespace fieldnames;
    const QString execute = QString("CREATE TABLE IF NOT EXISTS " + TableName + "(" +
                                        Id + " INTEGER PRIMARY KEY," +
                                        Type + " TEXT," +
                                        Username + " TEXT"
                                    ");");

    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot create table %s: %s",
               qPrintable(TableName), qPrintable(query.lastError().text()));
    }
}

void SqlDatabase::createChatParticipantsTable()
{
    using namespace db::chat_participants;
    using namespace fieldnames;
    const QString execute = QString("CREATE TABLE IF NOT EXISTS " + TableName + "(" +
                                        Id + " INTEGER PRIMARY KEY," +
                                        ChatId + " INTEGER," +
                                        UserId + " INTEGER,"
                                    "   FOREIGN KEY(" + ChatId + ") REFERENCES " + db::chats::TableName + "(" + db::chats::fieldnames::Id + "),"
                                    "   FOREIGN KEY(" + UserId + ") REFERENCES " + db::users::TableName + "(" + db::users::fieldnames::Id + ")"
                                    ");");

    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot create table %s: %s",
               qPrintable(TableName), qPrintable(query.lastError().text()));
    }
}

void SqlDatabase::createMessagesTable()
{
    using namespace db::messages;
    using namespace fieldnames;
    const QString execute = QString("CREATE TABLE IF NOT EXISTS " + TableName + "(" +
                                        Id + " INTEGER PRIMARY KEY," +
                                        FromUserId + " INTEGER," +
                                        ChatId + " INTEGER," +
                                        Text + " TEXT," +
                                        Date + " TEXT,"
                                    "   FOREIGN KEY(" + FromUserId + ") REFERENCES " + db::users::TableName + "(" + db::users::fieldnames::Id + "),"
                                    "   FOREIGN KEY(" + ChatId + ") REFERENCES " + db::chats::TableName + "(" + db::chats::fieldnames::Id + ")"
                                    ");"
                                    );
    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot create table %s: %s",
               qPrintable(TableName), qPrintable(query.lastError().text()));
    }
}

void SqlDatabase::initTables()
{
    usersTable_ = new UsersTable(this);
    chatsTable_ = new ChatsTable(this);
    messagesTable_ = new MessagesTable(this);

    userServerTable_ = new UsersServerTable(this);
    serverLogsTable_ = new ServerLogsTable(this);
}

ServerLogsTable *SqlDatabase::serverLogsTable() const
{
    return serverLogsTable_;
}

#ifdef ABDUCHAT_CLIENT
void SqlDatabase::createChatsView()
{
    using namespace db;
    using namespace chats_view;
    using namespace fieldnames;
    auto lastMessage = [](const QString& column)->QString {
        return "(SELECT" + column + "FROM messages WHERE chat_id = chats.id ORDER BY messages.id DESC LIMIT 1)";
    };
    const QString execute = QString("CREATE VIEW " + ViewName + " AS " +
                                    "SELECT DISTINCT " +
                                        chats::fieldnames::Id + " AS " + ChatId + "," +
                                        chats::fieldnames::Type + " AS " + ChatType + "," +
                                        chats::fieldnames::Username + " AS " + ChatUsername + "," +
                                        lastMessage(messages::fieldnames::Text) + " AS " + LastMessage + "," +
                                        lastMessage(messages::fieldnames::FromUserId) + " AS " + FromUser + "," +
                                        lastMessage(messages::fieldnames::Date) + " AS " + Date + " " +
                                    "FROM " + chats::TableName +
                                    "INNER JOIN " + messages::TableName + " ON " + messages::fieldnames::ChatId + " = " + chats::fieldnames::Id +
                                    ");"
                                    );

    QSqlQuery query;
    if (query.exec(execute)) {
        qFatal("Cannot create view %s: %s",
               qPrintable(ViewName), qPrintable(query.lastError().text()));
    }
}
#endif

#ifdef ABDUCHAT_SERVER
void SqlDatabase::createServerLogsTable()
{
    using namespace db::server_logs;
    using namespace fieldnames;
    const QString execute = QString("CREATE TABLE IF NOT EXISTS" + TableName + "(" +
                                        Id + " INTEGER PRIMARY KEY," +
                                        Text + " TEXT," +
                                        Date + " TEXT"
                                               ");"
                                    );
    QSqlQuery query;
    if (query.exec(execute)) {
        qFatal("Cannot create table %s: %s",
               qPrintable(TableName), qPrintable(query.lastError().text()));
    }
}

void SqlDatabase::createUsersServerTable()
{
    using namespace db::users_server;
    using namespace fieldnames;
    const QString execute = QString("CREATE TABLE IF NOT EXISTS " + TableName + "(" +
                                        Id + " INTEGER PRIMARY KEY" +
                                        Password + " TEXT,"
                                    "   FOREIGN KEY(" + Id + ") REFERENCES " + db::users::TableName + "(" + db::users::fieldnames::Id + ")"
                                    ");"
                                    );
    QSqlQuery query;
    if (query.exec(execute)) {
        qFatal("Cannot create table %s: %s",
               qPrintable(TableName), qPrintable(query.lastError().text()));
    }
}
#endif












