#include "loginpage.h"
#include "ui_loginpage.h"

LoginPage::LoginPage(QWidget *parent)
    : QWidget{parent}
    , ui_(new ui::LoginPage)
{
    ui_->setupUi(this);
}
