#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

namespace ui {
    class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT
public:
    explicit LoginPage(QWidget *parent = nullptr);

private:
    ui::LoginPage* ui_ = nullptr;
};

#endif // LOGINPAGE_H
