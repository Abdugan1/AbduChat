#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QRegularExpression>

class QSizePolicy;
class QSpacerItem;

namespace constants {

namespace widget {

extern const int InitPageWidth;
extern const int InitPageHeight;

} // widget

namespace regexes {

extern const QRegularExpression UsernameRegex;
extern const QRegularExpression PasswordRegex;
extern const QRegularExpression NameRegex;

} // regexes

namespace ui {

QSpacerItem* createHSpacer();

QSpacerItem* createVSpacer();

extern const QSizePolicy MaximumMaximum;

} // ui

} // constants

#endif // CONSTANTS_H
