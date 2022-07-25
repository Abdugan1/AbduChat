#include "ui_conversationwidget.h"
#include "conversationheader.h"
#include "conversationview.h"
#include "messagelineedit.h"

#include <QFrame>
#include <QBoxLayout>

void UiConversationWidget::setupUi(QWidget *conversationWidget)
{
    header = new ConversationHeader;
    header->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    conversationView = new ConversationView;

    messageLineEdit = new MessageLineEdit;

    mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(header);
    mainLayout->addWidget(conversationView);
    mainLayout->addWidget(messageLineEdit);

    conversationWidget->setObjectName("conversationWidget");
    conversationWidget->setLayout(mainLayout);
}
