#include "mainwindow.h"
#include "loginpage.h"
#include "mainpage.h"

#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , loginPage_(new LoginPage)
    , mainPage_(new MainPage)
    , stackedWidget_(new QStackedWidget)
{
    stackedWidget_->addWidget(loginPage_);
    stackedWidget_->addWidget(mainPage_);
    stackedWidget_->setCurrentIndex(1);

    resize(1000, 640);
    setCentralWidget(stackedWidget_);
}
