#include "chatsviewtable.h"
#include "database_names.h"

namespace FieldNames = db::chats_view::fieldnames;
namespace FieldNums  = db::chats_view::fieldnums;

ChatsViewTable::ChatsViewTable(QObject *parent)
    : SqlTableModel{parent}
{
    setTable(db::chats_view::ViewName);
    createRoleNames();
    select();
}

void ChatsViewTable::createRoleNames()
{
    QHash<int, QByteArray> roleNames;
    roleNames[FieldNums::ChatId        + Qt::UserRole] = qPrintable(FieldNames::ChatId);
    roleNames[FieldNums::ChatType      + Qt::UserRole] = qPrintable(FieldNames::ChatType);
    roleNames[FieldNums::User1Id       + Qt::UserRole] = qPrintable(FieldNames::User1Id);
    roleNames[FieldNums::User2Id       + Qt::UserRole] = qPrintable(FieldNames::User2Id);
    roleNames[FieldNums::User1Username + Qt::UserRole] = qPrintable(FieldNames::User1Username);
    roleNames[FieldNums::User2Username + Qt::UserRole] = qPrintable(FieldNames::User2Username);
    roleNames[FieldNums::LastMessage   + Qt::UserRole] = qPrintable(FieldNames::LastMessage);
    roleNames[FieldNums::FromUser      + Qt::UserRole] = qPrintable(FieldNames::FromUser);
    roleNames[FieldNums::Date          + Qt::UserRole] = qPrintable(FieldNames::Date);

    setRoleNames(roleNames);
}
