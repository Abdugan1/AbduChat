#ifndef CHATLISTDOCKWIDGET_H
#define CHATLISTDOCKWIDGET_H

#include <QDockWidget>

namespace ui {
    class ChatListDockWidget;
}

class ChatListDockWidget : public QDockWidget
{
public:
    explicit ChatListDockWidget(QWidget* parent = nullptr);

private:
    ui::ChatListDockWidget* ui_ = nullptr;
};

#endif // CHATLISTDOCKWIDGET_H
