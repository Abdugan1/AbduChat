#include "validatedlineedit.h"

#include <QLabel>
#include <QBoxLayout>
#include <QDebug>

ValidatedLineEdit::ValidatedLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , iconLabel_(new QLabel)
{
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(iconLabel_);
    hLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum));

    this->setLayout(hLayout);
}

void ValidatedLineEdit::setValidator(const QValidator *validator)
{
    QLineEdit::setValidator(validator);
}

void ValidatedLineEdit::setIcon(const QPixmap &icon)
{
    iconLabel_->setPixmap(icon);
    setTextMargins(icon.width() + 10, 0, 0, 0);
}
