#include "connectionerrorpage.h"
#include "ui_connectionerrorpage.h"
#include "pushbutton.h"

#include <AbduChatClient/chatclient.h>

ConnectionErrorPage::ConnectionErrorPage(QWidget *parent)
    : QWidget{parent}
    , ui_{new UiConnectionErrorPage}
{
    ui_->setupUi(this);

    connect(ui_->reconnectButton, &PushButton::clicked, &ChatClient::instance(), &ChatClient::connectToHost);
}
