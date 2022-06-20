#ifndef USERSTABLE_H
#define USERSTABLE_H

#include "sqltablemodel.h"

class User;

class UsersTable : public SqlTableModel
{
    Q_OBJECT
public:
    explicit UsersTable(QObject* parent = nullptr);

protected:
    void addUser(const User& user);

private:
    void createRoleNames();

    void addUserRecord(const QSqlRecord& userRecord);

    friend class SqlDatabase;
};

#endif // USERSTABLE_H
