#include "sqldatabase.h"
#include "database_names.h"
#include "logger.h"

#include "userstable.h"
#include "chatstable.h"
#include "messagestable.h"
#include "usersservertable.h"
#include "serverlogstable.h"

#include <QSqlQuery>
#include <QSqlRecord>
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

void SqlDatabase::addUser(const UserPtr &user)
{
    usersTable_->addUser(user);
}

void SqlDatabase::addChat(const ChatPtr &chat)
{
    chatsTable_->addChat(chat);
}

void SqlDatabase::addMessage(const MessagePtr &message)
{
    messagesTable_->addMessage(message);
}

void SqlDatabase::connectToDatabase()
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.isValid()) {
        database = QSqlDatabase::addDatabase("QSQLITE");
        if (!database.isValid())
            Logger::fatal("SqlDatabase::connectToDatabase::Database is not valid. reason: "
                          + database.lastError().text());
    }

    const QDir writeDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (!writeDir.mkpath("."))
        Logger::fatal("SqlDatabase::connectToDatabase::Make writable directory failed. path: "
                      + writeDir.absolutePath());

    // Ensure that we have a writable location on all devices.
    const QString fileName = writeDir.absolutePath() + "/AbduChat.sqlite3";
    // When using the SQLite driver, open() will create the SQLite database if it doesn't exist.
    database.setDatabaseName(fileName);
    if (!database.open()) {
        QFile::remove(fileName);
        Logger::fatal("SqlDatabase::connectToDatabase::Open database failed. reason: "
                      + database.lastError().text());
    }
}

void SqlDatabase::createTables()
{
    createUsersTable();
    createChatsTable();
    createMessagesTable();
}

void SqlDatabase::createUsersTable()
{
    using namespace db::users;
    using namespace fieldnames;
    const QString execute = QString("CREATE TABLE IF NOT EXISTS " + TableName + "(" +
                                        Id + " INTEGER PRIMARY KEY," +
                                        FirstName + " TEXT," +
                                        LastName + " TEXT," +
                                        Username + " TEXT," +
                                        Date + " TEXT"
                                    ");");

    QSqlQuery query;
    if (!query.exec(execute)) {
        Logger::fatal("SqlDatabase::createUsersTable::Create table failed. reason: "
                      + query.lastError().text());
    }
}

void SqlDatabase::createChatsTable()
{
    using namespace db::chats;
    using namespace fieldnames;
    const QString execute = QString("CREATE TABLE IF NOT EXISTS " + TableName + "(" +
                                        Id + " INTEGER PRIMARY KEY," +
                                        Type + " TEXT," +
                                        User1Id + " INTEGER," +
                                        User2Id + " INTEGER," +
                                    "   FOREIGN KEY(" + User1Id + ") REFERENCES " + db::users::TableName + "(" + db::users::fieldnames::Id + "),"
                                    "   FOREIGN KEY(" + User2Id + ") REFERENCES " + db::users::TableName + "(" + db::users::fieldnames::Id + ")"
                                    ");");

    QSqlQuery query;
    if (!query.exec(execute)) {
        Logger::fatal("SqlDatabase::createChatsTable::Create table failed. reason: "
                      + query.lastError().text());
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
        Logger::fatal("SqlDatabase::createMessagesTable::Create table failed. reason: "
                      + query.lastError().text());
    }
}

void SqlDatabase::initTables()
{
    usersTable_ = new UsersTable(this);
    chatsTable_ = new ChatsTable(this);
    messagesTable_ = new MessagesTable(this);
}
