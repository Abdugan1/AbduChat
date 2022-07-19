#include "pushbutton.h"

PushButton::PushButton(QWidget *parent)
    : QPushButton(parent)
{
    setObjectName("button");
}

PushButton::PushButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setObjectName("button");
}

PushButton::PushButton(const QIcon &icon, const QString &text, QWidget *parent)
    : QPushButton(icon, text, parent)
{
    setObjectName("button");
}
