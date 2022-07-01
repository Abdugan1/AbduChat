#ifndef CHATSTABLE_H
#define CHATSTABLE_H

#include "sqltablemodel.h"
#include "chat.h"

class ChatsTable : public SqlTableModel
{
    Q_OBJECT
public:
    explicit ChatsTable(QObject *parent = nullptr);

protected:
    void addChat(const ChatPtr& chat);

public slots:
    bool hasChat(int user1Id, int user2Id) const;

private:
    void createRoleNames();

    void addChatRecord(const QSqlRecord& chatRecord);

    friend class SqlDatabase;
};

#endif // CHATSTABLE_H
