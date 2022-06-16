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
    names[FieldNums::Id         + Qt::UserRole] = FieldNames::Id;
    names[FieldNums::FromUserId + Qt::UserRole] = FieldNames::FromUserId;
    names[FieldNums::ChatId     + Qt::UserRole] = FieldNames::ChatId;
    names[FieldNums::Text       + Qt::UserRole] = FieldNames::Text;
    names[FieldNums::Date       + Qt::UserRole] = FieldNames::Date;
    return names;
}

void MessagesTableServer::insertMessage(const Message &message)
{
    QSqlRecord newRecord = record();

    // Because 'id' is PK. So it is default auto-incremented
    if (message.id() != -1)
        newRecord.setValue(FieldNames::Id, message.id());

    newRecord.setValue(FieldNames::FromUserId,  message.from().id());
    newRecord.setValue(FieldNames::ChatId,      message.chat().id());
    newRecord.setValue(FieldNames::Text,        message.text());
    newRecord.setValue(FieldNames::Date,        message.date());

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

//    const QString execute = QString("CREATE TABLE IF NOT EXISTS '%1' (" // messages
//                                    "   '%2' INTEGER PRIMARY KEY," // message_id
//                                    "   '%3' INT NOT NULL," // from_user_id
//                                    "   '%4' INT NOT NULL," // to_user_id
//                                    "   '%5' TEXT NOT NULL," // text
//                                    "   '%6' TEXT NOT NULL"  // sent_datetime
//                                    ")")
//            .arg(db::messages::TableName)
//            .arg(FieldNames::MessageId)
//            .arg(FieldNames::FromUserId)
//            .arg(FieldNames::ToUserId)
//            .arg(FieldNames::Text)
//            .arg(FieldNames::Date);

//    QSqlQuery query;
//    if (!query.exec(execute)) {
//        qFatal("Cannot create table '%s': %s",
//               qPrintable(db::messages::TableName),
//               qPrintable(query.lastError().text()));
//    }
}
