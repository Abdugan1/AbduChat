#include "ui_sidepanel.h"
#include "constants.h"
#include "lineedit.h"
#include "chatsview.h"
#include "chatdelegate.h"

#include <AbduChatLib/sqldatabaseclient.h>
#include <AbduChatLib/chatsviewtable.h>

#include <QPushButton>
#include <QStringListModel>
#include <QBoxLayout>
#include <QDebug>

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

    chatsView = new ChatsView;

    mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(chatsView);

    sidePanel->setObjectName("sidePanel");
    sidePanel->setLayout(mainLayout);
}
