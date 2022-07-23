#include "ui_mainpage.h"
#include "sidepanel.h"
#include "lineedit.h"
#include "constants.h"

#include <QSplitter>
#include <QListView>
#include <QDebug>

void UiMainPage::setupUi(QSplitter *mainPage)
{
    sidePanel = new SidePanel;

    chatView = new QListView;

    mainPage->resize(constants::widget::InitPageWidth,
                     constants::widget::InitPageHeight);

    mainPage->addWidget(sidePanel);
    mainPage->addWidget(chatView);
    mainPage->setStretchFactor(1, 1);

    sidePanel->resize(mainPage->width() * 0.1, mainPage->height());
}
