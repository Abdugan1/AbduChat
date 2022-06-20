#include "chatstable.h"
#include "database_names.h"
#include "chat.h"

#include <QSqlRecord>
#include <QSqlError>

namespace FieldNames = db::chats::fieldnames;
namespace FieldNums = db::chats::fieldnums;

ChatsTable::ChatsTable(QObject *parent)
    : SqlTableModel{parent}
{
    setTable(db::chats::TableName);
    createRoleNames();
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

void ChatsTable::createRoleNames()
{
    QHash<int, QByteArray> roleNames;
    roleNames[FieldNums::Id       + Qt::UserRole] = qPrintable(FieldNames::Id);
    roleNames[FieldNums::Type     + Qt::UserRole] = qPrintable(FieldNames::Type);
    roleNames[FieldNums::Username + Qt::UserRole] = qPrintable(FieldNames::Username);
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
