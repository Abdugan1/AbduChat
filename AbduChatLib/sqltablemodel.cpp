#include "sqltablemodel.h"

#include <QSqlRecord>

SqlTableModel::SqlTableModel(QObject *parent)
    : QSqlTableModel{parent}
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant SqlTableModel::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> SqlTableModel::roleNames() const
{
    return roleNames_;
}

void SqlTableModel::setRoleNames(const QHash<int, QByteArray> &newRoleNames)
{
    roleNames_ = newRoleNames;
}
