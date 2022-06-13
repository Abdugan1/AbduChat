#include "messagestableclient.h"
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

MessagesTableClient::MessagesTableClient(QObject *parent)
    : QSqlTableModel{parent}
{
    createTable();
    setTable(db::messages::TableName);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setSort(FieldNums::MessageId, Qt::DescendingOrder);
}

QVariant MessagesTableClient::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> MessagesTableClient::roleNames() const
{
    QHash<int, QByteArray> names;
    names[FieldNums::MessageId      + Qt::UserRole] = FieldNames::MessageId;
    names[FieldNums::FromUserId     + Qt::UserRole] = FieldNames::FromUserId;
    names[FieldNums::ToUserId       + Qt::UserRole] = FieldNames::ToUserId;
    names[FieldNums::Text           + Qt::UserRole] = FieldNames::Text;
    names[FieldNums::SentDatetime   + Qt::UserRole] = FieldNames::SentDatetime;
    return names;
}

int MessagesTableClient::recipientId() const
{
    return recipientId_;
}

void MessagesTableClient::setRecipientId(int id)
{
    if (recipientId_ == id)
        return;
    recipientId_ = id;

    const QString filterString = QString("(from_user_id = '%1' AND to_user_id = '%2') "
                                         "OR (from_user_id = '%2' AND to_user_id = '%1')")
            .arg(myId()).arg(recipientId());
    setFilter(filterString);
    select();

    emit recipientIdChanged();
}

int MessagesTableClient::myId() const
{
    return myId_;
}

void MessagesTableClient::setMyId(int id)
{
    if (myId_ == id)
        return;
    myId_ = id;
    emit myIdChanged();
}

void MessagesTableClient::insertMessages(const QJsonArray &messages)
{
    for (const auto& messageRef : messages) {
        const QJsonObject messageJson = messageRef.toObject();
        const int messageId = messageJson.value(reply::headers::Id).toInt();
        Message message = jsonToMessageSentDatetimeIsFromJsonObject(messageJson, messageId);
        insertMessageWithoutSubmit(message);
    }

    if (!submitAll())
        qFatal("Cannot submit messages: %s", qPrintable(lastError().text()));

    select();
}

void MessagesTableClient::insertMessage(const Message &message)
{
    insertMessageWithoutSubmit(message);

    if (!submitAll())
        qFatal("Cannot submit messages: %s", qPrintable(lastError().text()));

    select();
}

void MessagesTableClient::insertMessageWithoutSubmit(const Message &message)
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
}

void MessagesTableClient::createTable()
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
