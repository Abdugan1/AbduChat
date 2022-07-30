#include "constants.h"
#include <QSpacerItem>

namespace constants {

namespace widget {
    const int InitPageWidth = 1000;
    const int InitPageHeight = 640;
} // widget

namespace regexes {
    const QRegularExpression UsernameRegex = QRegularExpression("^[a-zA-Z0-9]([\\._-](?![\\._-])|[a-zA-Z0-9]){2,18}[a-zA-Z0-9]$");
    const QRegularExpression PasswordRegex = QRegularExpression("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$");
    const QRegularExpression NameRegex     = QRegularExpression("^[a-z][a-z ,\\.'-]+[a-z\\.]$");
} // regexes

namespace ui {

QSpacerItem* createHSpacer()
{
    return new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
}

QSpacerItem* createVSpacer()
{
    return new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
}

const QSizePolicy MaximumMaximum = QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

}

} // constatns
