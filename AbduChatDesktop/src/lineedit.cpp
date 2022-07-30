#include "lineedit.h"
#include "label.h"

#include <QBoxLayout>
#include <QValidator>
#include <QPropertyAnimation>
#include <QDebug>

const int Margin = 10;

LineEdit::LineEdit(QWidget *parent)
    : QLineEdit(parent)
    , leftPixmap_(new Label)
    , rightPixmap_(new Label)
{
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(Margin, 0, Margin, 0);
    hLayout->addWidget(leftPixmap_);
    hLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum));
    hLayout->addWidget(rightPixmap_);

    setLayout(hLayout);
    setObjectName("lineEdit");

    borderColorAnimation_ = new QPropertyAnimation{this, "borderColor"};
    borderColorAnimation_->setDuration(300);
    borderColorAnimation_->setStartValue(QColor{0, 0, 0});
    borderColorAnimation_->setEndValue(QColor{255, 0, 0});
}

void LineEdit::setValidator(const QValidator *validator)
{
    QLineEdit::setValidator(validator);
}

void LineEdit::setLeftPixmap(const QPixmap &icon)
{
    leftPixmap_->setPixmap(icon);
    auto margins = textMargins();
    margins.setLeft(icon.width() + Margin + 5);
    setTextMargins(margins);
}

void LineEdit::setRightPixmap(const QPixmap &icon)
{
    rightPixmap_->setPixmap(icon);
    auto margins = textMargins();
    margins.setRight(icon.width() + Margin + 5);
    setTextMargins(margins);
}

void LineEdit::setLeftPixmapClickable(bool on)
{
    leftPixmap_->setClickable(on);
}

void LineEdit::setRightPixmapClickable(bool on)
{
    rightPixmap_->setClickable(on);
}

Label *LineEdit::leftPixmap() const
{
    return leftPixmap_;
}

Label *LineEdit::rightPixmap() const
{
    return rightPixmap_;
}

void LineEdit::setBorderColor(const QColor &color)
{
    QLineEdit::setStyleSheet(QString("LineEdit{border: 1px solid rgb(%1, %2, %3)}")
                             .arg(color.red()).arg(color.green()).arg(color.blue()));
}

void LineEdit::focusInEvent(QFocusEvent *event)
{
    setBorderColor(QColor{0, 0, 0});
    QLineEdit::focusInEvent(event);
}

void LineEdit::focusOutEvent(QFocusEvent *event)
{
    if (validator() && !hasAcceptableInput()) {
        makeBorderRed();
    }
    QLineEdit::focusOutEvent(event);
}

void LineEdit::makeBorderRed()
{
    borderColorAnimation_->start();
}
