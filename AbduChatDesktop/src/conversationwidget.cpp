#include "conversationwidget.h"
#include "ui_conversationwidget.h"

ConversationWidget::ConversationWidget(QWidget *parent)
    : QWidget{parent}
    , ui_(new UiConversationWidget)
{
    ui_->setupUi(this);
}
