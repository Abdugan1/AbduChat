#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class LoginPage;
class MainPage;
class QStackedWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:


private:
    LoginPage* loginPage_ = nullptr;
    MainPage* mainPage_ = nullptr;

    QStackedWidget* stackedWidget_ = nullptr;
};

#endif // MAINWINDOW_H
