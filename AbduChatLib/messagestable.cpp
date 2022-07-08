#include "messagestable.h"
#include "database_names.h"
#include "request_and_reply_constants.h"
#include "message.h"
#include "logger.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJSValue>

namespace FieldNames = db::messages::fieldnames;
namespace FieldNums = db::messages::fieldnums;

MessagesTable::MessagesTable(QObject *parent)
    : SqlTableModel{parent}
    , currentChat_(new Chat(this))
{
    setTable(db::messages::TableName);
    createRoleNames();
    select();
}

Chat *MessagesTable::currentChat() const
{
    return currentChat_;
}

void MessagesTable::addMessage(const MessagePtr &message)
{
    QSqlRecord messageRecord = record();
    message->toSqlRecord(&messageRecord);
    addMessageRecord(messageRecord);

    if (!submitAll()) {
        Logger::fatal("MessagesTable::addMessage::Submit all failed. id: "
                         + QString::number(message->id()) + " | reason: "
                         + lastError().text()
                      );
    }
}

void MessagesTable::setCurrentChat(const ChatPtr &newCurrentChat)
{
    if (currentChat_->isEqual(newCurrentChat.get()))
        return;
    currentChat_->copyValues(newCurrentChat.get());
    qDebug() << "Current chat:" << currentChat_->toJson();
    selectCurrentChatValues();
    emit currentChatChanged();
}

void MessagesTable::createRoleNames()
{
    QHash<int, QByteArray> names;
    names[FieldNums::Id         + Qt::UserRole] = qPrintable(FieldNames::Id);
    names[FieldNums::FromUserId + Qt::UserRole] = qPrintable(FieldNames::FromUserId);
    names[FieldNums::ChatId     + Qt::UserRole] = qPrintable(FieldNames::ChatId);
    names[FieldNums::Text       + Qt::UserRole] = qPrintable(FieldNames::Text);
    names[FieldNums::Date       + Qt::UserRole] = qPrintable(FieldNames::Date);
    setRoleNames(names);
}

void MessagesTable::addMessageRecord(const QSqlRecord &messageRecord)
{
    if (!insertRecord(rowCount(), messageRecord)) {
        Logger::fatal("MessagesTable::addMessageRecord::Insert record failed. id: "
                      + messageRecord.value(FieldNames::Id).toString() + " | reason: "
                      + lastError().text()
                      );
    }
}

void MessagesTable::selectCurrentChatValues()
{
    const QString filterString(FieldNames::ChatId + " = " + QString::number(currentChat_->id()));
    setFilter(filterString);
    select();
}
