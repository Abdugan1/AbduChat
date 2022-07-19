#ifndef UI_CHATLISTDOCKWIDGET_H
#define UI_CHATLISTDOCKWIDGET_H

class QDockWidget;
class QFrame;
class LineEdit;
class QPushButton;
class QListView;
class QVBoxLayout;
class QHBoxLayout;

namespace ui {

class ChatListDockWidget
{
public:
    QHBoxLayout* topLayout = nullptr;
    QPushButton* openSideMenuButton = nullptr;
    LineEdit* searchEdit = nullptr;

    QListView* chatsView = nullptr;

    QVBoxLayout* mainLayout = nullptr;
    QFrame* background = nullptr;

    void setupUi(QDockWidget* chatListDockWidget);
};

} // namespace ui

#endif // UI_CHATLISTDOCKWIDGET_H
