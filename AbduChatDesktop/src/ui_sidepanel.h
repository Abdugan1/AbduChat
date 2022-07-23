#ifndef UISIDEPANEL_H
#define UISIDEPANEL_H

class QWidget;
class QPushButton;
class LineEdit;
class QListView;
class QHBoxLayout;
class QVBoxLayout;

class UiSidePanel
{
public:
    QPushButton* openSideMenuButton = nullptr; // Like Qt Quick Drawer
    LineEdit* searchEdit = nullptr;
    QHBoxLayout* topLayout = nullptr;

    QListView* chatsView = nullptr;

    QVBoxLayout* mainLayout = nullptr;

    void setupUi(QWidget* sidePanel = nullptr);
};

#endif // UISIDEPANEL_H
