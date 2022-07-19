#include "ui_mainpage.h"
#include "chatlistdockwidget.h"
#include "lineedit.h"
#include "constants.h"

#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QListView>
#include <QBoxLayout>

namespace ui {

void MainPage::setupUi(QWidget *mainPage)
{
    if (mainPage->objectName().isEmpty())
        mainPage->setObjectName("mainPage");


    chatListDockWidget = new ::ChatListDockWidget;

    chatView = new QListView;

    mainPage->resize(constants::widget::InitPageWidth,
                     constants::widget::InitPageHeight);
}

} // namespace ui
