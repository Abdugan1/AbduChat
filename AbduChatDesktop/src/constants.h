#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QRegularExpression>
#include <QSizePolicy>

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

const QSizePolicy MaximumMaximum = QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

} // ui

} // constants

#endif // CONSTANTS_H
