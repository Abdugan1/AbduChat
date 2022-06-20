#ifndef SQLTABLEMODEL_H
#define SQLTABLEMODEL_H

#include <QSqlTableModel>

class SqlTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit SqlTableModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;
    void setRoleNames(const QHash<int, QByteArray>& newRoleNames);

private:
    QHash<int, QByteArray> roleNames_;
};

#endif // SQLTABLEMODEL_H
