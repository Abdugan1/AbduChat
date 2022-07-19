#include "constants.h"

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

} // constatns
