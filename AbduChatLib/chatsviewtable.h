#ifndef CHATSVIEWTABLE_H
#define CHATSVIEWTABLE_H

#include "sqltablemodel.h"

class ChatsViewTable : public SqlTableModel
{
    Q_OBJECT
public:
    explicit ChatsViewTable(QObject *parent = nullptr);

private:
    void createRoleNames();

};

#endif // CHATSVIEWTABLE_H
