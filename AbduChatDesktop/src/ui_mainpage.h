#ifndef UI_MAINPAGE_H
#define UI_MAINPAGE_H

class ChatListDockWidget;
class QWidget;
class QFrame;
class QLabel;
class QPushButton;
class LineEdit;
class QListView;
class QVBoxLayout;
class QHBoxLayout;

namespace ui {

class MainPage
{
public:
    ChatListDockWidget* chatListDockWidget = nullptr;

    QListView* chatView = nullptr;

    void setupUi(QWidget* mainPage);
};

} // namespace ui

#endif // UI_MAINPAGE_H
