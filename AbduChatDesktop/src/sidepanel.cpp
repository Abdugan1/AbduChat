#include "sidepanel.h"
#include "ui_sidepanel.h"
#include "chatsview.h"

#include <AbduChatLib/database_names.h>

#include <QDebug>

SidePanel::SidePanel(QWidget *parent)
    : QWidget(parent)
    , ui_(new UiSidePanel)
{
    ui_->setupUi(this);

    connect(ui_->chatsView, &QAbstractItemView::pressed, this, [this](const QModelIndex& index) {
        if (index.isValid()) {
            int chatId = index.data(Qt::UserRole + db::chats_view::fieldnums::ChatId).toInt();
            qDebug() << "chat pressed:" << chatId;
            emit chatPressed(chatId);
        }
    });
}
