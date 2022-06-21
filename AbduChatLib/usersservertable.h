#ifndef USERSSERVERTABLE_H
#define USERSSERVERTABLE_H

#include "sqltablemodel.h"

class User;

class UsersServerTable : public SqlTableModel
{
    Q_OBJECT
public:
    explicit UsersServerTable(QObject *parent = nullptr);

    bool hasUser(const QString& username, const QString& password);

    QSqlRecord getUser(const QString& username) const;

protected:
    bool addUser(const User& user, const QString& password);

private:
    void createRoleNames();

    bool addUserRecord(const QSqlRecord& userRecord);

    friend class SqlDatabaseServer;
};

#endif // USERSSERVERTABLE_H
