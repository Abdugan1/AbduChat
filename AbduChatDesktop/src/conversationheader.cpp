#include "conversationheader.h"

#include <QLabel>
#include <QBoxLayout>

inline QSpacerItem* createHSpacer()
{
    return new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
}

ConversationHeader::ConversationHeader(QWidget *parent)
    : QFrame{parent}
{
    titleLabel_ = new QLabel("Username");

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(titleLabel_);
    layout->addSpacerItem(createHSpacer());

    setObjectName("conversationHeader");
    setLayout(layout);
}
