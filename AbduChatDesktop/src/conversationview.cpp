#include "conversationview.h"
#include "messagedelegate.h"

#include <AbduChatLib/sqldatabaseclient.h>
#include <AbduChatLib/messagestable.h>

ConversationView::ConversationView(QWidget *parent)
    : QListView{parent}
{
    setModel(SqlDatabaseClient::instance().messagesTable());
    setItemDelegate(new MessageDelegate(this));
    setSpacing(3);
}
