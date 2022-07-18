#ifndef LOGINPAGEFORM_H
#define LOGINPAGEFORM_H

#include <QWidget>

namespace Ui {
class LoginPageForm;
}

class LoginPageForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPageForm(QWidget *parent = nullptr);
    ~LoginPageForm();

private:
    Ui::LoginPageForm *ui;
};

#endif // LOGINPAGEFORM_H
