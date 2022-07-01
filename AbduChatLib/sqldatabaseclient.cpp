#include "sqldatabaseclient.h"
#include "database_names.h"
#include "chatsviewtable.h"
#include "messagestable.h"
#include "user.h"
#include "message.h"
#include "logger.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

SqlDatabaseClient::SqlDatabaseClient(QObject *parent)
    : SqlDatabase{parent}
{
    createClientTables();
    initClientTables();
    messagesTable()->setSort(db::messages::fieldnums::Id, Qt::DescendingOrder);
    messagesTable()->select();
}

ChatsViewTable *SqlDatabaseClient::chatsViewTable() const
{
    return chatsViewTable_;
}

void SqlDatabaseClient::addUsers(const QJsonArray &users)
{
    for (const auto& userRef : users) {
        const QJsonObject user = userRef.toObject();
        addUser(UserPtr(User::fromJson(user)));
    }
}

void SqlDatabaseClient::addMessages(const QJsonArray &messages)
{
    for (const auto& messageRef : messages) {
        const QJsonObject message = messageRef.toObject();
        addMessage(MessagePtr(Message::fromJson(message)));
    }
}

void SqlDatabaseClient::createClientTables()
{
    createChatsViewTable();
}

void SqlDatabaseClient::createChatsViewTable()
{
    using namespace db;
    using namespace chats_view;
    using namespace fieldnames;
    auto lastMessage = [](const QString& column)->QString {
        return "(SELECT " + column + " FROM " + db::messages::TableName + " WHERE chat_id = chats.id ORDER BY messages.id DESC LIMIT 1)";
    };
    auto username = [](const QString& id)->QString {
        return "(SELECT username FROM users WHERE users.id =" + id + ")";
    };
    const QString execute = QString("CREATE VIEW IF NOT EXISTS " + ViewName + " AS " +
                                    "SELECT DISTINCT " +
                                        "chats." + chats::fieldnames::Id + " AS " + ChatId + "," +
                                        "chats." + chats::fieldnames::Type + " AS " + ChatType + "," +
                                        "chats." + chats::fieldnames::User1Id + " AS " + User1Id + "," +
                                        "chats." + chats::fieldnames::User2Id + " AS " + User2Id + "," +
                                        lastMessage(messages::fieldnames::Text) + " AS " + LastMessage + "," +
                                        lastMessage(messages::fieldnames::FromUserId) + " AS " + FromUser + "," +
                                        lastMessage(messages::fieldnames::Date) + " AS " + Date + "," +
                                        username(chats::fieldnames::User1Id) + " AS " + User1Username + "," +
                                        username(chats::fieldnames::User2Id) + " AS " + User2Username + " " +
                                    "FROM " + chats::TableName + " " +
                                    "LEFT JOIN " + messages::TableName + " ON messages." + messages::fieldnames::ChatId + " = chats." + chats::fieldnames::Id
                                    );

    QSqlQuery query;
    if (!query.exec(execute)) {
        Logger::fatal("SqlDatabaseClient::createChatsViewTable::Create table failed. reason: "
                      + query.lastError().text());
    }
}

void SqlDatabaseClient::initClientTables()
{
    chatsViewTable_ = new ChatsViewTable(this);
}
