#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class LoginPage;
class MainPage;
class ConnectionErrorPage;
class SlidingStackedWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:


private:
    enum PageIndex {
        ConnectionError,
        Login,
        Main
    };

    ConnectionErrorPage* connectionErrorPage_ = nullptr;
    LoginPage* loginPage_ = nullptr;
    MainPage* mainPage_ = nullptr;

    SlidingStackedWidget* stackedWidget_ = nullptr;
};

#endif // MAINWINDOW_H
