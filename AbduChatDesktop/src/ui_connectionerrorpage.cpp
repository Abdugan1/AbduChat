#include "ui_connectionerrorpage.h"
#include "pushbutton.h"
#include "constants.h"

#include <QLabel>
#include <QBoxLayout>
#include <QMovie>

void UiConnectionErrorPage::setupUi(QWidget *connectionErrorPage)
{
    noConnectionImageLabel = new QLabel;
    noConnectionImageLabel->setMovie(new QMovie{":/images/no_connection.gif", QByteArray(), noConnectionImageLabel});
    noConnectionImageLabel->movie()->start();

    titleLabel = new QLabel{QObject::tr("Whoops!")};
    QFont titleFont;
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    reasonLabel = new QLabel{QObject::tr("Connection error")};
    QFont reasonFont;
    reasonFont.setPointSize(12);
    reasonLabel->setFont(reasonFont);

    reconnectButton = new PushButton{QObject::tr("TRY AGAIN")};
    reconnectButton->setObjectName("reconnectButton");

    mainLayout = new QVBoxLayout;
    mainLayout->addSpacerItem(constants::ui::createVSpacer());
    mainLayout->addWidget(noConnectionImageLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(titleLabel,             0, Qt::AlignCenter);
    mainLayout->addWidget(reasonLabel,            0, Qt::AlignCenter);
    mainLayout->addWidget(reconnectButton,        0, Qt::AlignCenter);
    mainLayout->addSpacerItem(constants::ui::createVSpacer());

    connectionErrorPage->setObjectName("connectionErrorPage");
    connectionErrorPage->setLayout(mainLayout);
}
