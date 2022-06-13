#ifndef USERSTABLE_H
#define USERSTABLE_H

#include <QSqlTableModel>

class UsersTable : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit UsersTable(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    bool hasUser(const QString& username, const QString& password);
    bool insertUser(const QString& username, const QString& password);

    QSqlRecord getUser(const QString& username) const;

private:
    void createTable();
};

#endif // USERSTABLE_H
