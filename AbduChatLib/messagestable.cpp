#include "messagestable.h"
#include "database_names.h"
#include "message.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

namespace FieldNames = db::messages::fieldnames;
namespace FieldNums = db::messages::fieldnums;

MessagesTable::MessagesTable(QObject *parent)
    : QSqlTableModel{parent}
{
    createTable();
    setTable(db::messages::TableName);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

QVariant MessagesTable::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> MessagesTable::roleNames() const
{
    QHash<int, QByteArray> names;
    names[FieldNums::MessageId      + Qt::UserRole] = FieldNames::MessageId;
    names[FieldNums::FromUser       + Qt::UserRole] = FieldNames::FromUser;
    names[FieldNums::ToUser         + Qt::UserRole] = FieldNames::ToUser;
    names[FieldNums::Text           + Qt::UserRole] = FieldNames::Text;
    names[FieldNums::SentDatetime   + Qt::UserRole] = FieldNames::SentDatetime;
    return names;
}

void MessagesTable::insertMessage(const Message &message)
{
    const QString sentDatetime = message.sentDatetime().toString(Qt::ISODate);

    QSqlRecord newRecord = record();
    newRecord.setValue(FieldNames::MessageId, message.id());
    newRecord.setValue(FieldNames::FromUser, message.fromUser());
    newRecord.setValue(FieldNames::ToUser, message.toUser());
    newRecord.setValue(FieldNames::Text, message.text());
    newRecord.setValue(FieldNames::SentDatetime, sentDatetime);

    if (!insertRecord(rowCount(), newRecord)) {
        qFatal("Cannot insert '%s' to %s: %s",
               qPrintable(message.text()),
               qPrintable(tableName()),
               qPrintable(lastError().text()));
    }

    if (!submitAll()) {
        qFatal("Cannot submit '%s' to %s: %s",
               qPrintable(message.text()),
               qPrintable(tableName()),
               qPrintable(lastError().text()));
    }
}

void MessagesTable::createTable()
{
    if (QSqlDatabase::database().tables().contains(db::messages::TableName))
        return;

    const QString execute = QString("CREATE TABLE IF NOT EXISTS '%1' (" // messages
                                    "   '%2' INTEGER PRIMARY KEY," // message_id
                                    "   '%3' TEXT NOT NULL," // from_user
                                    "   '%4' TEXT NOT NULL," // to_user
                                    "   '%5' TEXT NOT NULL," // text
                                    "   '%6' TEXT NOT NULL"  // sent_datetime
                                    ")")
            .arg(db::messages::TableName)
            .arg(FieldNames::MessageId)
            .arg(FieldNames::FromUser)
            .arg(FieldNames::ToUser)
            .arg(FieldNames::Text)
            .arg(FieldNames::SentDatetime);

    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot create table '%s': %s",
               qPrintable(db::messages::TableName),
               qPrintable(query.lastError().text()));
    }
}
