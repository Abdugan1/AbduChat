#include "mainwindow.h"
#include "loginpage.h"
#include "mainpage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , loginPage_(new LoginPage)
    , mainPage_(new MainPage)
{
    addDockWidget(Qt::LeftDockWidgetArea, mainPage_->dockWidget());
    setCentralWidget(mainPage_->centralWidget());
}
