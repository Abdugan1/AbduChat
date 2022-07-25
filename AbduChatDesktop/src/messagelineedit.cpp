#include "messagelineedit.h"

MessageLineEdit::MessageLineEdit(QWidget *parent)
    : QLineEdit{parent}
{
    setPlaceholderText(tr("Write a message..."));
}
