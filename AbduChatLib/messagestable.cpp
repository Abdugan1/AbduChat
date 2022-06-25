#include "messagestable.h"
#include "database_names.h"
#include "request_and_reply_constants.h"
#include "message.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QJsonArray>
#include <QJsonObject>

namespace FieldNames = db::messages::fieldnames;
namespace FieldNums = db::messages::fieldnums;

MessagesTable::MessagesTable(QObject *parent)
    : SqlTableModel{parent}
{
    setTable(db::messages::TableName);
    setSort(FieldNums::Id, Qt::DescendingOrder);
    createRoleNames();
    select();
}

void MessagesTable::addMessage(const Message &message)
{
    QSqlRecord messageRecord = record();
    message.toSqlRecord(&messageRecord);
    addMessageRecord(messageRecord);

    if (!submitAll()) {
        qFatal("Cannot submit add message:\nid: %d\n text: %s\nreason: %s",
               message.id(),
               qPrintable(message.text()),
               qPrintable(lastError().text())
               );
    }
}

void MessagesTable::createRoleNames()
{
    QHash<int, QByteArray> names;
    names[FieldNums::Id         + Qt::UserRole] = qPrintable(FieldNames::Id);
    names[FieldNums::FromUserId + Qt::UserRole] = qPrintable(FieldNames::FromUserId);
    names[FieldNums::ChatId     + Qt::UserRole] = qPrintable(FieldNames::ChatId);
    names[FieldNums::Text       + Qt::UserRole] = qPrintable(FieldNames::Text);
    names[FieldNums::Date       + Qt::UserRole] = qPrintable(FieldNames::Date);
    setRoleNames(names);
}

void MessagesTable::addMessageRecord(const QSqlRecord &messageRecord)
{
    if (!insertRecord(rowCount(), messageRecord)) {
        qFatal("Cannot insert add message:\nid: %d\n text: %s\nreason: %s",
               messageRecord.value(FieldNames::Id).toInt(),
               qPrintable(messageRecord.value(FieldNames::Text).toString()),
               qPrintable(lastError().text())
               );
    }
}
