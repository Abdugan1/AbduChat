#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

class UiLoginPage;

class LoginPage : public QWidget
{
    Q_OBJECT
public:
    explicit LoginPage(QWidget *parent = nullptr);

private:
    UiLoginPage* ui_ = nullptr;
};

#endif // LOGINPAGE_H
