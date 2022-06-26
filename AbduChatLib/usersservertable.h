#ifndef USERSSERVERTABLE_H
#define USERSSERVERTABLE_H

#include "sqltablemodel.h"
#include <memory>

class User;
using UserPtr = std::shared_ptr<User>;

class UsersServerTable : public SqlTableModel
{
    Q_OBJECT
public:
    explicit UsersServerTable(QObject *parent = nullptr);

    bool hasUser(const QString& username, const QString& password);

protected:
    bool addUser(const UserPtr& user, const QString& password);

private:
    void createRoleNames();

    bool addUserRecord(const QSqlRecord& userRecord);

    friend class SqlDatabaseServer;
};

#endif // USERSSERVERTABLE_H
