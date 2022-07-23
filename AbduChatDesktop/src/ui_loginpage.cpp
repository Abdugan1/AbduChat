#include "ui_loginpage.h"
#include "lineedit.h"
#include "pushbutton.h"
#include "label.h"
#include "constants.h"

#include <QFrame>
#include <QBoxLayout>
#include <QMovie>
#include <QStateMachine>
#include <QState>
#include <QRegularExpressionValidator>

QSpacerItem* createHSpacer()
{
    return new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
}

QSpacerItem* createVSpacer()
{
    return new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
}

void setPointSize(QWidget* w, int pointSize)
{
    w->setFont(QFont(w->font().family(), pointSize));
}

void UiLoginPage::setupUi(QWidget *loginPage)
{
    // Left frame
    appLogoLabel = new QLabel;
    appLogoLabel->setPixmap(QPixmap(":/images/app_logo_32.png"));
    appLogoLabel->setSizePolicy(constants::ui::MaximumMaximum);

    appNameLabel = new QLabel;
    appNameLabel->setText("AbduChat");
    appNameLabel->setSizePolicy(constants::ui::MaximumMaximum);

    appInfoLayout = new QHBoxLayout;
    appInfoLayout->addWidget(appLogoLabel);
    appInfoLayout->addWidget(appNameLabel);
    appInfoLayout->addSpacerItem(createHSpacer());

    welcomeLabel = new QLabel(QObject::tr("Welcome to the official\nAbduChat Desktop app"));
    welcomeLabel->setAlignment(Qt::AlignCenter);
    setPointSize(welcomeLabel, 22);

    leftSideLayout = new QVBoxLayout;
    leftSideLayout->addLayout(appInfoLayout);
    leftSideLayout->addSpacerItem(createVSpacer());
    leftSideLayout->addWidget(welcomeLabel);
    leftSideLayout->addSpacerItem(createVSpacer());

    leftSide = new QLabel;
    leftSide->setMovie(new QMovie(":/images/welcome_background.gif"));
    leftSide->movie()->start();
    leftSide->movie()->setSpeed(200);
    leftSide->setLayout(leftSideLayout);


    // Right frame
    loginLabel = new QLabel(QObject::tr("Login"));
    setPointSize(loginLabel, 18);

    usernameEdit = new LineEdit;
    qDebug() << "username is valid?" << constants::regexes::UsernameRegex.isValid();
    usernameEdit->setValidator(new QRegularExpressionValidator(constants::regexes::UsernameRegex));
    usernameEdit->setLeftPixmap(QPixmap(":/images/user_24.png"));
    usernameEdit->setPlaceholderText(QObject::tr("Username"));

    passwordEdit = new LineEdit;
    qDebug() << "password is valid?" << constants::regexes::PasswordRegex.isValid();
    passwordEdit->setValidator(new QRegularExpressionValidator(constants::regexes::PasswordRegex));
    passwordEdit->setLeftPixmap(QPixmap(":/images/padlock_24.png"));
    passwordEdit->setRightPixmap(QPixmap(":/images/show_password_24.png"));
    passwordEdit->setRightPixmapClickable(true);
    passwordEdit->setPlaceholderText(QObject::tr("Password"));

    QStateMachine *stateMachine = new QStateMachine(loginPage);
    QState* hiddenPasswordState = new QState;
    QState* shownPasswordState = new QState;

    hiddenPasswordState->assignProperty(passwordEdit, "echoMode", QLineEdit::Password);
    hiddenPasswordState->assignProperty(passwordEdit->rightPixmap(), "pixmap", QPixmap(":/images/show_password_24.png"));
    hiddenPasswordState->addTransition(passwordEdit->rightPixmap(), &Label::pressed, shownPasswordState);

    shownPasswordState->assignProperty(passwordEdit, "echoMode", QLineEdit::Normal);
    shownPasswordState->assignProperty(passwordEdit->rightPixmap(), "pixmap", QPixmap(":/images/hide_password_24.png"));
    shownPasswordState->addTransition(passwordEdit->rightPixmap(), &Label::pressed, hiddenPasswordState);

    stateMachine->addState(hiddenPasswordState);
    stateMachine->addState(shownPasswordState);
    stateMachine->setInitialState(hiddenPasswordState);
    stateMachine->start();

    loginButton = new PushButton(QObject::tr("LOGIN"));

    editLayout = new QVBoxLayout;
    editLayout->setSpacing(10);
    editLayout->addWidget(loginLabel);
    editLayout->addWidget(usernameEdit);
    editLayout->addWidget(passwordEdit);
    editLayout->addWidget(loginButton);

    goToSignUpPageLabel = new QLabel(QObject::tr("Don't have an account yet? <a href=\":\">Sign up</a>"));
    setPointSize(goToSignUpPageLabel, 11);

    rightSideLayout = new QVBoxLayout;
    rightSideLayout->addSpacerItem(createVSpacer());
    rightSideLayout->addLayout(editLayout);
    rightSideLayout->addSpacerItem(createVSpacer());
    rightSideLayout->addWidget(goToSignUpPageLabel);
//    rightSideLayout->addSpacerItem(createVSpacer());

    rightSide = new QFrame;
    rightSide->setLayout(rightSideLayout);


    // Main layout
    mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(leftSide);
    mainLayout->addWidget(rightSide);

    loginPage->resize(constants::widget::InitPageWidth,
                      constants::widget::InitPageHeight);

    loginPage->setLayout(mainLayout);
}
