#include "ui_loginpage.h"
#include "validatedlineedit.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QBoxLayout>
#include <QMovie>

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

namespace ui {

void LoginPage::setupUi(QWidget *loginPage)
{
    const QSizePolicy MaximumMaximum = QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    if (loginPage->objectName().isEmpty())
        loginPage->setObjectName("LoginPage");


    // Left frame
    appLogoLabel = new QLabel;
    appLogoLabel->setPixmap(QPixmap(":/images/app_logo_32.png"));
    appLogoLabel->setSizePolicy(MaximumMaximum);

    appNameLabel = new QLabel;
    appNameLabel->setText("AbduChat");
    appNameLabel->setSizePolicy(MaximumMaximum);

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

    usernameEdit = new ValidatedLineEdit;
    usernameEdit->setIcon(QPixmap(":/images/user_24.png"));
    usernameEdit->setPlaceholderText(QObject::tr("Username"));

    passwordEdit = new ValidatedLineEdit;
    passwordEdit->setIcon(QPixmap(":/images/padlock_24.png"));
    passwordEdit->setPlaceholderText(QObject::tr("Password"));

    loginButton = new QPushButton(QObject::tr("LOGIN"));

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

    loginPage->resize(1050, 640);
    loginPage->setLayout(mainLayout);
}

} // namespace ui
