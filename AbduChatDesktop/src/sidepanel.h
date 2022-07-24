#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QWidget>

class UiSidePanel;

class SidePanel : public QWidget
{
    Q_OBJECT
public:
    explicit SidePanel(QWidget* parent = nullptr);

signals:
    void chatPressed(int chatId);

private:
    UiSidePanel* ui_ = nullptr;
};

#endif // SIDEPANEL_H
