#include "chatstable.h"
#include "database_names.h"
#include "chat.h"
#include "logger.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QJsonObject>
#include <QJsonDocument>

namespace FieldNames = db::chats::fieldnames;
namespace FieldNums = db::chats::fieldnums;

ChatsTable::ChatsTable(QObject *parent)
    : SqlTableModel{parent}
{
    setTable(db::chats::TableName);
    createRoleNames();
    select();
}

bool ChatsTable::hasChat(int user1Id, int user2Id) const
{
    const QString execute = QString("SELECT COUNT(*) FROM " + db::chats::TableName + " " +
                                    "WHERE (" + FieldNames::User1Id + "=:user1Id AND " + FieldNames::User2Id + "=:user2Id) "
                                    "OR (" + FieldNames::User1Id + "=:user2Id AND " + FieldNames::User2Id + "=:user1Id)"
                                    );
    QSqlQuery query;
    query.prepare(execute);
    query.bindValue(":user1Id", user1Id);
    query.bindValue(":user2Id", user2Id);
    if (!query.exec()) {
        Logger::fatal("ChatsTable::hasChat::Get count of chat failed. user_1_id: "
                      + QString::number(user1Id) + " | user_2_id: "
                      + QString::number(user2Id) + " | reason: "
                      + query.lastError().text());
    }
    query.next();
    Logger::debug("ChatsTable::hasChat::Result: " + QVariant(query.value(0).toBool()).toString());
    return query.value(0).toBool();
}

Chat *ChatsTable::getChat(int chatId) const
{
    const QString execute = "SELECT * FROM chats WHERE id = :chatId";
    QSqlQuery query;
    query.prepare(execute);
    query.bindValue(":chatId", chatId);
    if (!query.exec()) {
        Logger::fatal("ChatsTable::getChat::Get chat failed. id: "
                      + QString::number(chatId) + " | reason: "
                      + query.lastError().text());
    }
    query.next();
    Chat* chat = Chat::fromSqlRecord(query.record());
    Logger::debug("ChatsTable::getChat::Result chat: "
                  + QString(QJsonDocument(chat->toJson()).toJson()));
    return chat;
}

Chat *ChatsTable::getChat(int user1Id, int user2Id) const
{
    const QString execute = "SELECT * FROM chats WHERE user_1_id = :user1Id AND user_2_id = :user2Id";
    QSqlQuery query;
    query.prepare(execute);
    query.bindValue(":user1Id", user1Id);
    query.bindValue(":user2Id", user2Id);
    if (!query.exec()) {
        Logger::fatal("ChatsTable::getChat::Get chat failed. user1Id: "
                      + QString::number(user1Id) + " | user2Id: "
                      + QString::number(user2Id) + " | reason: "
                      + query.lastError().text());
    }
    query.next();
    Chat* chat = Chat::fromSqlRecord(query.record());
    Logger::debug("ChatsTable::getChat::Result chat: "
                  + QString(QJsonDocument(chat->toJson()).toJson()));
    return chat;
}

void ChatsTable::setFilterByUserId(int id)
{
    const QString filterString(FieldNames::User1Id + "=" + id + " OR " + FieldNames::User2Id + "=" + id);
    setFilter(filterString);
    select();
}


void ChatsTable::addChat(const ChatPtr &chat)
{
    QSqlRecord chatRecord = record();
    chat->toSqlRecord(&chatRecord);
    addChatRecord(chatRecord);

    if (!submitAll()) {
        Logger::fatal("ChatsTable::addChat::Submit all failed. id: "
                      + QString::number(chat->id()) + " | reason: "
                      + lastError().text());
    }
}

void ChatsTable::createRoleNames()
{
    QHash<int, QByteArray> roleNames;
    roleNames[FieldNums::Id       + Qt::UserRole] = qPrintable(FieldNames::Id);
    roleNames[FieldNums::Type     + Qt::UserRole] = qPrintable(FieldNames::Type);
    roleNames[FieldNums::User1Id  + Qt::UserRole] = qPrintable(FieldNames::User1Id);
    roleNames[FieldNums::User2Id  + Qt::UserRole] = qPrintable(FieldNames::User2Id);
    roleNames[FieldNums::Date     + Qt::UserRole] = qPrintable(FieldNames::Date);
    setRoleNames(roleNames);
}

void ChatsTable::addChatRecord(const QSqlRecord &chatRecord)
{
    if (!insertRecord(rowCount(), chatRecord)) {
        Logger::fatal("ChatsTable::addChatRecord::Insert record failed. id: "
                      + chatRecord.value(FieldNames::Id).toString() + " | reason: "
                      + lastError().text()
                      );
    }
}
