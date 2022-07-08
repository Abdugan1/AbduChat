#ifndef USERSTABLE_H
#define USERSTABLE_H

#include "sqltablemodel.h"
#include "user.h"

class UsersTable : public SqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(QString filterValue READ filterValue WRITE setFilterValue RESET resetFilterValue NOTIFY filterValueChanged)
public:
    explicit UsersTable(QObject* parent = nullptr);

    const QString &filterValue() const;
    void setFilterValue(const QString &newFilterValue);
    void resetFilterValue();

    Q_INVOKABLE QString getUsername(int userId) const;

signals:
    void filterValueChanged();

protected:
    void addUser(const UserPtr& user);

private:
    void createRoleNames();

    void addUserRecord(const QSqlRecord& userRecord);

private:
    QString filterValue_;

    friend class SqlDatabase;
};

#endif // USERSTABLE_H
