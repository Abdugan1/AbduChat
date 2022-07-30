#ifndef UICONNECTIONERRORPAGE_H
#define UICONNECTIONERRORPAGE_H

class QWidget;
class QLabel;
class PushButton;
class QHBoxLayout;
class QVBoxLayout;

class UiConnectionErrorPage
{
public:
    QLabel* noConnectionImageLabel = nullptr;
    QLabel* titleLabel = nullptr;
    QLabel* reasonLabel = nullptr;
    PushButton* reconnectButton = nullptr;
    QVBoxLayout* mainLayout = nullptr;

    void setupUi(QWidget* connectionErrorPage);
};

#endif // UICONNECTIONERRORPAGE_H
