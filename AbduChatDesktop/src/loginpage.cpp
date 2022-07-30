#include "loginpage.h"
#include "ui_loginpage.h"
#include "pushbutton.h"
#include "lineedit.h"

#include <AbduChatClient/chatclient.h>

LoginPage::LoginPage(QWidget *parent)
    : QWidget{parent}
    , ui_(new UiLoginPage)
{
    ui_->setupUi(this);

    connect(ui_->loginButton, &PushButton::clicked, this, &LoginPage::loggedIn);
}

void LoginPage::tryLogin()
{
    if (ui_->usernameEdit->hasAcceptableInput() && ui_->passwordEdit->hasAcceptableInput()) {
        QString username = ui_->usernameEdit->text();
        QString password = ui_->passwordEdit->text();
        ChatClient::instance().attempToLogIn(username, password);
    }
}
