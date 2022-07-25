#ifndef CONVERSATIONHEADER_H
#define CONVERSATIONHEADER_H

#include <QFrame>

class QLabel;

class ConversationHeader : public QFrame
{
    Q_OBJECT
public:
    explicit ConversationHeader(QWidget* parent = nullptr);

private:
    QLabel* titleLabel_ = nullptr;
};

#endif // CONVERSATIONHEADER_H
