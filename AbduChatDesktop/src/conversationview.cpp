#include "conversationview.h"
#include "messagedelegate.h"

#include <AbduChatLib/sqldatabaseclient.h>
#include <AbduChatLib/messagestable.h>

#include <QGuiApplication>
#include <QPainter>
#include <QDebug>

ConversationView::ConversationView(QWidget *parent)
    : QListView{parent}
    , background_(":/images/chat_background.png")
{
    setModel(SqlDatabaseClient::instance().messagesTable());
    setItemDelegate(new MessageDelegate(this));
    setSpacing(3);
}

void ConversationView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this->viewport());
    painter.drawPixmap(0, 0, background_.scaled(this->size(), Qt::KeepAspectRatioByExpanding));
    QListView::paintEvent(event);
}
