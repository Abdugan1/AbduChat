#include "serverlogstable.h"
#include "database_names.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

namespace FieldNames = db::server_logs::fieldnames;
namespace FieldNums = db::server_logs::fieldnums;

ServerLogsTable::ServerLogsTable(QObject *parent)
    : SqlTableModel{parent}
{
    setTable(db::server_logs::TableName);
    select();
}

void ServerLogsTable::insertLog(const QString &text, const QString &insertDatetime)
{
    QSqlRecord newRecord = record();
    newRecord.setValue(FieldNames::Text, text);
    newRecord.setValue(FieldNames::Date, insertDatetime);

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

void ServerLogsTable::createRoleNames()
{
    QHash<int, QByteArray> names;
    names[FieldNums::Id   + Qt::UserRole] = qPrintable(FieldNames::Id);
    names[FieldNums::Text + Qt::UserRole] = qPrintable(FieldNames::Text);
    names[FieldNums::Date + Qt::UserRole] = qPrintable(FieldNames::Date);
    setRoleNames(names);
}
