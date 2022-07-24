#ifndef CHATSVIEW_H
#define CHATSVIEW_H

#include <QListView>

class ChatsView : public QListView
{
    Q_OBJECT
public:
    explicit ChatsView(QWidget* parent = nullptr);
};

#endif // CHATSVIEW_H
