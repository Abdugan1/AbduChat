#include "mainpage.h"
#include "ui_mainpage.h"
#include "chatlistdockwidget.h"

#include <QListView>

MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
    , ui_(new ui::MainPage)
{
    ui_->setupUi(this);
}

QDockWidget *MainPage::dockWidget() const
{
    return ui_->chatListDockWidget;
}

QWidget *MainPage::centralWidget() const
{
    return ui_->chatView;
}
