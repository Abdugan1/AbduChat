#ifndef CHATSTABLE_H
#define CHATSTABLE_H

#include "sqltablemodel.h"
#include "chat.h"

class ChatsTable : public SqlTableModel
{
    Q_OBJECT
public:
    explicit ChatsTable(QObject *parent = nullptr);

    Q_INVOKABLE bool hasChat(int user1Id, int user2Id) const;

    Chat* getChat(int chatId) const;
    Chat* getChat(int user1Id, int user2Id) const;

public slots:
    void setFilterByUserId(int id);

protected:
    void addChat(const ChatPtr& chat);

private:
    void createRoleNames();

    void addChatRecord(const QSqlRecord& chatRecord);

    friend class SqlDatabase;
};

#endif // CHATSTABLE_H
