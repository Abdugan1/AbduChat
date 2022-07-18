#include "loginpageform.h"
#include "ui_loginpageform.h"

LoginPageForm::LoginPageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginPageForm)
{
    ui->setupUi(this);
}

LoginPageForm::~LoginPageForm()
{
    delete ui;
}
