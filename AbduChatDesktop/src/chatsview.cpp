#include "chatsview.h"
#include "chatdelegate.h"

#include <AbduChatLib/sqldatabaseclient.h>
#include <AbduChatLib/chatsviewtable.h>

ChatsView::ChatsView(QWidget *parent)
    : QListView{parent}
{
    setObjectName("chatsView");
    setMouseTracking(true);

    // without this, ChatDelegate option will have wrong size!!!
#ifdef Q_OS_LINUX
    show();
#endif
    setModel(SqlDatabaseClient::instance().chatsViewTable());
    setItemDelegate(new ChatDelegate(this));
    setSelectionMode(QAbstractItemView::SingleSelection);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}
