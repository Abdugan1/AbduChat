#include "ui_sidepanel.h"
#include "constants.h"
#include "lineedit.h"
#include "chatdelegate.h"

#include <AbduChatLib/sqldatabaseclient.h>
#include <AbduChatLib/chatsviewtable.h>

#include <QPushButton>
#include <QListView>
#include <QStringListModel>
#include <QBoxLayout>

void UiSidePanel::setupUi(QWidget *sidePanel)
{
    openSideMenuButton = new QPushButton("=");
    openSideMenuButton->setSizePolicy(constants::ui::MaximumMaximum);

    searchEdit = new LineEdit;
    searchEdit->setObjectName("searchEdit");

    topLayout = new QHBoxLayout;
    topLayout->setContentsMargins(5, 5, 5, 5);
    topLayout->setSpacing(5);
    topLayout->addWidget(openSideMenuButton);
    topLayout->addWidget(searchEdit);

    chatsView = new QListView;
    chatsView->setMouseTracking(true);

    // without this, ChatDelegate option will have wrong size!!!
#ifdef Q_OS_LINUX
    chatsView->show();
#endif
    chatsView->setModel(SqlDatabaseClient::instance().chatsViewTable());
    chatsView->setItemDelegate(new ChatDelegate(chatsView));

    mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(chatsView);

    sidePanel->setLayout(mainLayout);
}
