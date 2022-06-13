#include "contactstable.h"
#include "database_names.h"
#include "request_and_reply_constants.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

namespace FieldNames = db::contacts::fieldnames;
namespace FieldNums = db::contacts::fieldnums;

ContactsTable::ContactsTable(QObject *parent)
    : QSqlTableModel{parent}
{
    createTable();
    setTable(db::contacts::TableName);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant ContactsTable::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> ContactsTable::roleNames() const
{
    QHash<int, QByteArray> names;
    names[FieldNums::Id             + Qt::UserRole] = FieldNames::Id;
    names[FieldNums::Username       + Qt::UserRole] = FieldNames::Username;
    names[FieldNums::InsertDatetime + Qt::UserRole] = FieldNames::InsertDatetime;
    return names;
}

int ContactsTable::myId() const
{
    return myId_;
}

void ContactsTable::setMyId(int newMyId)
{
    if (myId_ == newMyId)
        return;
    myId_ = newMyId;

    const QString filterString = QString("id != '%1'").arg(myId());
    setFilter(filterString);
    select();

    emit myIdChanged();
}


void ContactsTable::insertContacts(const QJsonArray &contacts)
{
    for (const auto& contactRef : contacts) {
        const QJsonObject contact = contactRef.toObject();
        const QString username = contact.value(reply::headers::Username).toString();
        const QString insertDatetime = contact.value(reply::headers::InsertDatetime).toString();
        insertContact(username, insertDatetime);
    }
}

void ContactsTable::insertContact(const QString &username, const QString &insertDatetime)
{
    QSqlRecord newRecord = record();
    newRecord.setValue(FieldNames::Username, username);
    newRecord.setValue(FieldNames::InsertDatetime, insertDatetime);

    if (!insertRecord(rowCount(), newRecord)) {
        qFatal("Cannot insert '%s' to %s: %s",
               qPrintable(username),
               qPrintable(tableName()),
               qPrintable(lastError().text()));
    }

    if (!submitAll()) {
        qFatal("Cannot submit '%s' to %s: %s",
               qPrintable(username),
               qPrintable(tableName()),
               qPrintable(lastError().text()));
    }

    select();
}

void ContactsTable::createTable()
{
    if (QSqlDatabase::database().tables().contains(db::contacts::TableName))
        return;

    const QString execute = QString("CREATE TABLE IF NOT EXISTS %1 (" // TableName: contacts
                                    " '%2' INTEGER PRIMARY KEY," // contact_id
                                    " '%3' TEXT NOT NULL," // username
                                    " '%4' TEXT NOT NULL" // insert_datetime
                                    ")")
            .arg(db::contacts::TableName)
            .arg(FieldNames::Id)
            .arg(FieldNames::Username)
            .arg(FieldNames::InsertDatetime);

    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot create table '%s': %s",
               qPrintable(tableName()),
               qPrintable(query.lastError().text()));
    }
}
