#ifndef CONVERSATIONWIDGET_H
#define CONVERSATIONWIDGET_H

#include <QWidget>

class UiConversationWidget;

class ConversationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConversationWidget(QWidget *parent = nullptr);

private:
    UiConversationWidget* ui_ = nullptr;
};

#endif // CONVERSATIONWIDGET_H
