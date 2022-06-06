#include "serverlogstable.h"
#include "database_names.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

namespace FieldNames = db::server_logs::fieldnames;
namespace FieldNums = db::server_logs::fieldnums;

ServerLogsTable::ServerLogsTable(QObject *parent)
    : QSqlTableModel{parent}
{
    createTable();
    setTable(db::server_logs::TableName);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

QVariant ServerLogsTable::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> ServerLogsTable::roleNames() const
{
    QHash<int, QByteArray> names;
    names[FieldNums::Id             + Qt::UserRole] = FieldNames::Id;
    names[FieldNums::Text           + Qt::UserRole] = FieldNames::Text;
    names[FieldNums::InsertDatetime + Qt::UserRole] = FieldNames::InsertDatetime;
    return names;
}

void ServerLogsTable::insertLog(const QString &text, const QString &insertDatetime)
{
    QSqlRecord newRecord = record();
    newRecord.setValue(FieldNames::Text, text);
    newRecord.setValue(FieldNames::InsertDatetime, insertDatetime);

    if (!insertRecord(rowCount(), newRecord)) {
        qFatal("Cannot insert '%s' to %s: %s",
               qPrintable(text),
               qPrintable(tableName()),
               qPrintable(lastError().text()));
    }

    if (!submitAll()) {
        qFatal("Cannot submit '%s' to %s: %s",
               qPrintable(text),
               qPrintable(tableName()),
               qPrintable(lastError().text()));
    }
    select();
}

void ServerLogsTable::createTable()
{
    if (QSqlDatabase::database().tables().contains(db::server_logs::TableName))
        return;

    const QString execute = QString("CREATE TABLE IF NOT EXISTS %1 (" // TableName: server_logs
                                    " '%2' INTEGER PRIMARY KEY," // contact_id
                                    " '%3' TEXT NOT NULL," // text
                                    " '%4' TEXT NOT NULL" // data_insert
                                    ")")
            .arg(db::server_logs::TableName)
            .arg(FieldNames::Id)
            .arg(FieldNames::Text)
            .arg(FieldNames::InsertDatetime);

    QSqlQuery query;
    if (!query.exec(execute)) {
        qFatal("Cannot create table '%s': %s",
               qPrintable(tableName()),
               qPrintable(query.lastError().text()));
    }
}
