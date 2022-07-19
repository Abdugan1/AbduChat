#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>

namespace ui {
    class MainPage;
}

class QDockWidget;

class MainPage : public QWidget
{
public:
    explicit MainPage(QWidget* parent = nullptr);

    QDockWidget* dockWidget() const;
    QWidget* centralWidget() const;

private:
    ui::MainPage* ui_ = nullptr;
};

#endif // MAINPAGE_H
