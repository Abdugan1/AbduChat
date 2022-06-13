#include "messagestableserver.h"
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

MessagesTableServer::MessagesTableServer(QObject *parent)
    : QSqlTableModel{parent}
{
    createTable();
    setTable(db::messages::TableName);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

QVariant MessagesTableServer::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> MessagesTableServer::roleNames() const
{
    QHash<int, QByteArray> names;
    names[FieldNums::MessageId      + Qt::UserRole] = FieldNames::MessageId;
    names[FieldNums::FromUserId     + Qt::UserRole] = FieldNames::FromUserId;
    names[FieldNums::ToUserId       + Qt::UserRole] = FieldNames::ToUserId;
    names[FieldNums::Text           + Qt::UserRole] = FieldNames::Text;
    names[FieldNums::SentDatetime   + Qt::UserRole] = FieldNames::SentDatetime;
    return names;
}

void MessagesTableServer::insertMessage(const Message &message)
{
    QSqlRecord newRecord = record();

    if (message.id() != -1)
        newRecord.setValue(FieldNames::MessageId, message.id());

    newRecord.setValue(FieldNames::FromUserId, message.fromUserId());
    newRecord.setValue(FieldNames::ToUserId, message.toUserId());
    newRecord.setValue(FieldNames::Text, message.text());
    newRecord.setValue(FieldNames::SentDatetime, message.sentDatetime());

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

    select();
}

void MessagesTableServer::createTable()
{
    if (QSqlDatabase::database().tables().contains(db::messages::TableName))
        return;

    const QString execute = QString("CREATE TABLE IF NOT EXISTS '%1' (" // messages
                                    "   '%2' INTEGER PRIMARY KEY," // message_id
                                    "   '%3' INT NOT NULL," // from_user_id
                                    "   '%4' INT NOT NULL," // to_user_id
                                    "   '%5' TEXT NOT NULL," // text
                                    "   '%6' TEXT NOT NULL"  // sent_datetime
                                    ")")
            .arg(db::messages::TableName)
            .arg(FieldNames::MessageId)
            .arg(FieldNames::FromUserId)
            .arg(FieldNames::ToUserId)
            .arg(FieldNames::Text)
            .arg(FieldNames::SentDatetime);

    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot create table '%s': %s",
               qPrintable(db::messages::TableName),
               qPrintable(query.lastError().text()));
    }
}
