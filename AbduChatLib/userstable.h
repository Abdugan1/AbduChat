#ifndef USERSTABLE_H
#define USERSTABLE_H

#include "sqltablemodel.h"
#include "user.h"

class UsersTable : public SqlTableModel
{
    Q_OBJECT
public:
    explicit UsersTable(QObject* parent = nullptr);

protected:
    void addUser(const UserPtr& user);

private:
    void createRoleNames();

    void addUserRecord(const QSqlRecord& userRecord);

    friend class SqlDatabase;
};

#endif // USERSTABLE_H
