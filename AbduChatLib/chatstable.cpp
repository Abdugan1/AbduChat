#include "chatstable.h"
#include "database_names.h"
#include "chat.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

namespace FieldNames = db::chats::fieldnames;
namespace FieldNums = db::chats::fieldnums;

ChatsTable::ChatsTable(QObject *parent)
    : SqlTableModel{parent}
{
    setTable(db::chats::TableName);
    createRoleNames();
    select();
}

void ChatsTable::addChat(const Chat &chat)
{
    QSqlRecord chatRecord = record();
    chat.toSqlRecord(&chatRecord);
    addChatRecord(chatRecord);

    if (!submitAll()) {
        qFatal("Cannot insert chat:\nid: %d\nreason: %s",
               chat.id(),
               qPrintable(lastError().text())
               );
    }
}

bool ChatsTable::hasChat(int user1Id, int user2Id) const
{
    const QString execute = QString("SELECT COUNT(*) FROM " + db::chats::TableName +
                                    "WHERE " + FieldNames::User1Id + "=:user1Id AND " + FieldNames::User2Id + "=:user2Id"
                                    );
    QSqlQuery query;
    query.prepare(execute);
    query.bindValue("user1Id", user1Id);
    query.bindValue("user2Id", user2Id);
    if (!query.exec()) {
        qFatal("Cannot get count of chat: %s", qPrintable(query.lastError().text()));
    }
    query.next();
    return query.value(0).toBool();
}

void ChatsTable::createRoleNames()
{
    QHash<int, QByteArray> roleNames;
    roleNames[FieldNums::Id       + Qt::UserRole] = qPrintable(FieldNames::Id);
    roleNames[FieldNums::Type     + Qt::UserRole] = qPrintable(FieldNames::Type);
    roleNames[FieldNums::User1Id  + Qt::UserRole] = qPrintable(FieldNames::User1Id);
    roleNames[FieldNums::User2Id  + Qt::UserRole] = qPrintable(FieldNames::User2Id);
    roleNames[FieldNums::Date     + Qt::UserRole] = qPrintable(FieldNames::Date);
    setRoleNames(roleNames);
}

void ChatsTable::addChatRecord(const QSqlRecord &chatRecord)
{
    if (!insertRecord(rowCount(), chatRecord)) {
        qFatal("Cannot insert chat:\nid: %d\nreason: %s",
               chatRecord.value(FieldNames::Id).toInt(),
               qPrintable(lastError().text())
               );
    }
}
