#ifndef SERVERLOGSTABLE_H
#define SERVERLOGSTABLE_H

#include "sqltablemodel.h"

class ServerLogsTable : public SqlTableModel
{
    Q_OBJECT
public:
    explicit ServerLogsTable(QObject *parent = nullptr);

public slots:
    void insertLog(const QString& text, const QString& insertDatetime);

private:
    void createRoleNames();
};

#endif // SERVERLOGSTABLE_H
