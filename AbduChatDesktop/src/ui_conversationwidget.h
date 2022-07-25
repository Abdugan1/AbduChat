#ifndef UICONVERSATIONWIDGET_H
#define UICONVERSATIONWIDGET_H

class QWidget;
class ConversationHeader;
class ConversationView;
class MessageLineEdit;
class QHBoxLayout;
class QVBoxLayout;

class UiConversationWidget
{
public:
    ConversationHeader* header = nullptr;
    ConversationView* conversationView = nullptr;
    MessageLineEdit* messageLineEdit = nullptr;

    QVBoxLayout* mainLayout = nullptr;

    void setupUi(QWidget* conversationWidget);
};

#endif // UICONVERSATIONWIDGET_H
