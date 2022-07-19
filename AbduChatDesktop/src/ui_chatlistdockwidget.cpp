#include "ui_chatlistdockwidget.h"
#include "lineedit.h"
#include "constants.h"

#include <QDockWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QBoxLayout>
#include <QFrame>
#include <QListView>

namespace ui {

void ChatListDockWidget::setupUi(QDockWidget *chatListDockWidget)
{
    if (chatListDockWidget->objectName().isEmpty())
        chatListDockWidget->setObjectName("chatListDockWidget");

    openSideMenuButton = new QPushButton("=");
    openSideMenuButton->setSizePolicy(constants::ui::MaximumMaximum);

    searchEdit = new LineEdit;
    searchEdit->setObjectName("searchEdit");

    topLayout = new QHBoxLayout;
    topLayout->setContentsMargins(5, 5, 5, 5);
    topLayout->setSpacing(5);

    chatsView = new QListView;

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(chatsView);

    background = new QFrame;
    background->setLayout(mainLayout);

    chatListDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
    chatListDockWidget->setFeatures(chatListDockWidget->features() & ~QDockWidget::DockWidgetClosable
                                                                   & ~QDockWidget::DockWidgetMovable
                                                                   & ~QDockWidget::DockWidgetFloatable);
    chatListDockWidget->setWidget(background);
}


} // namespace ui
