#ifndef UI_LOGINPAGE_H
#define UI_LOGINPAGE_H

class QWidget;
class QLabel;
class QLineEdit;
class PushButton;
class QFrame;
class QHBoxLayout;
class QVBoxLayout;

class LineEdit;

namespace ui {

class LoginPage
{
public:
    QLabel* leftSide = nullptr;
    QVBoxLayout* leftSideLayout = nullptr;
    QHBoxLayout* appInfoLayout = nullptr;
    QLabel* appLogoLabel = nullptr;
    QLabel* appNameLabel = nullptr;
    QLabel* welcomeLabel = nullptr;

    QFrame* rightSide = nullptr;
    QVBoxLayout* rightSideLayout = nullptr;
    QVBoxLayout* editLayout = nullptr;
    QLabel* loginLabel = nullptr;
    LineEdit* usernameEdit = nullptr;
    LineEdit* passwordEdit = nullptr;
    PushButton* loginButton = nullptr;
    QLabel* goToSignUpPageLabel = nullptr;

    QHBoxLayout* mainLayout = nullptr;

    void setupUi(QWidget* loginPage);
};

} // namespace ui

#endif // UI_LOGINPAGE_H
