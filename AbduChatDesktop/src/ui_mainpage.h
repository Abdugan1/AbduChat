#ifndef UI_MAINPAGE_H
#define UI_MAINPAGE_H

class SidePanel;
class QSplitter;
class QFrame;
class QLabel;
class QPushButton;
class LineEdit;
class ConversationWidget;
class QVBoxLayout;
class QHBoxLayout;

class UiMainPage
{
public:
    SidePanel* sidePanel = nullptr;
    ConversationWidget* conversationWidget = nullptr;

    void setupUi(QSplitter* mainPage);
};


#endif // UI_MAINPAGE_H
