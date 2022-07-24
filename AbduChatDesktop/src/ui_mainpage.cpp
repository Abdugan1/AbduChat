#include "ui_mainpage.h"
#include "sidepanel.h"
#include "conversationview.h"
#include "lineedit.h"
#include "constants.h"

#include <QSplitter>
#include <QListView>
#include <QDebug>

void UiMainPage::setupUi(QSplitter *mainPage)
{
    sidePanel = new SidePanel;

    conversationView = new ConversationView;

    mainPage->resize(constants::widget::InitPageWidth,
                     constants::widget::InitPageHeight);

    mainPage->addWidget(sidePanel);
    mainPage->addWidget(conversationView);
    mainPage->setStretchFactor(1, 1);

    mainPage->setHandleWidth(0);

    sidePanel->resize(mainPage->width() * 0.1, mainPage->height());
}
