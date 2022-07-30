#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

class UiLoginPage;

class LoginPage : public QWidget
{
    Q_OBJECT
public:
    explicit LoginPage(QWidget *parent = nullptr);

signals:
    void loggedIn();

private slots:
    void tryLogin();

private:
    UiLoginPage* ui_ = nullptr;
};

#endif // LOGINPAGE_H
