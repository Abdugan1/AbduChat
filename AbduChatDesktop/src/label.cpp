#include "label.h"

#include <QDebug>

Label::Label(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f)
{
    setCursor(QCursor(Qt::PointingHandCursor));
    setClickable(false);
}

Label::Label(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text, parent, f)
{

}

bool Label::clickable() const
{
    return clickable_;
}

void Label::setClickable(bool on)
{
    clickable_ = on;
    setAttribute(Qt::WA_TransparentForMouseEvents, !clickable_);
}

void Label::mousePressEvent(QMouseEvent *event)
{
    QLabel::mousePressEvent(event);
    if (clickable_)
        emit pressed();
}

void Label::mouseReleaseEvent(QMouseEvent *event)
{
    QLabel::mouseReleaseEvent(event);
    if (clickable_)
        emit released();
}
