#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QWidget>

class UiSidePanel;

class SidePanel : public QWidget
{
public:
    explicit SidePanel(QWidget* parent = nullptr);

private:
    UiSidePanel* ui_ = nullptr;
};

#endif // SIDEPANEL_H
