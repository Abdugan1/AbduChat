#include "messagestable.h"
#include "database_names.h"
#include "request_and_reply_constants.h"
#include "chat.h"
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
{
    setTable(db::messages::TableName);
    createRoleNames();
    select();
}

Chat *MessagesTable::currentChat() const
{
    Logger::debug("MessagesTable::currentChat");
    if (currentChat_) {
        Logger::debug(QString::fromUtf8(QJsonDocument(currentChat_->toJson()).toJson()));
    }
    return currentChat_.get();
}

void MessagesTable::setCurrentChat(const QJSValue &newCurrentChat)
{
    Chat* chat = qobject_cast<Chat*>(newCurrentChat.toQObject());
    qDebug() << "newChat is null?" << (chat == nullptr) << chat->toJson();
    if (currentChat_.get() == chat)
        return;
    currentChat_ = std::shared_ptr<Chat>(chat);
    qDebug() << "Current chat:" << currentChat_->toJson();
    selectCurrentChatValues();
//    emit currentChatChanged();
}

//void MessagesTable::setCurrentChat(const QVariant &newCurrentChat)
//{
////    if (currentChat_ == std::make_shared<Chat>(qobject_cast<Chat*>(newCurrentChat.value<QObject*>())))
////        return;

//    if (dynamic_cast<Chat*>(newCurrentChat.value<QObject*>())) {
//        Logger::debug("MessagesTable::setCurrentChat::currentChat: no value: " + QString(newCurrentChat.typeName()));
//    }

//    Logger::debug("MessagesTable::setCurrentChat::currentChat: " + (currentChat_ == nullptr ? "null" : QString::fromUtf8(QJsonDocument(currentChat_->toJson()).toJson())));

//    currentChat_ = std::make_shared<Chat>(qobject_cast<Chat*>(newCurrentChat.value<QObject*>()));
//    selectCurrentChatValues();
//    emit currentChatChanged();
//}


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
