#include "mainwindow.h"
#include "loginpage.h"
#include "mainpage.h"
#include "slidingstackedwidget.h"
#include "connectionerrorpage.h"

#include <AbduChatClient/chatclient.h>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , connectionErrorPage_(new ConnectionErrorPage)
    , loginPage_(new LoginPage)
    , mainPage_(new MainPage)
    , stackedWidget_(new SlidingStackedWidget)
{
    stackedWidget_->addWidget(connectionErrorPage_);
    stackedWidget_->addWidget(loginPage_);
    stackedWidget_->addWidget(mainPage_);
    stackedWidget_->setCurrentIndex(PageIndex::Login);

    resize(1000, 640);
    setCentralWidget(stackedWidget_);

    connect(&ChatClient::instance(), &ChatClient::errorOccurred, this, [this]() {
        stackedWidget_->slideToIndex(PageIndex::ConnectionError);
    });

    connect(&ChatClient::instance(), &ChatClient::connected, this, [this]() {
        stackedWidget_->slideToIndex(PageIndex::Login);
    });

    connect(loginPage_, &LoginPage::loggedIn, this, [this]() {
        stackedWidget_->slideToIndex(PageIndex::Main);
    });
}
