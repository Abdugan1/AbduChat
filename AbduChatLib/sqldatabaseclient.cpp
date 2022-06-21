#include "sqldatabaseclient.h"
#include "database_names.h"
#include "chatsviewtable.h"

#include <QSqlQuery>
#include <QSqlError>

SqlDatabaseClient::SqlDatabaseClient(QObject *parent)
    : SqlDatabase{parent}
{
    createClientTables();
    initClientTables();
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

void SqlDatabaseClient::initClientTables()
{
    chatsViewTable_ = new ChatsViewTable(this);
}
