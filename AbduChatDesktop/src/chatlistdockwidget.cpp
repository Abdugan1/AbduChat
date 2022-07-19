#include "chatlistdockwidget.h"
#include "ui_chatlistdockwidget.h"

ChatListDockWidget::ChatListDockWidget(QWidget *parent)
    : QDockWidget(parent)
    , ui_(new ui::ChatListDockWidget)
{
    ui_->setupUi(this);
}
