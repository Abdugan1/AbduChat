#ifndef CONVERSATIONVIEW_H
#define CONVERSATIONVIEW_H

#include <QListView>

class ConversationView : public QListView
{
    Q_OBJECT
public:
    explicit ConversationView(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap background_;
};

#endif // CONVERSATIONVIEW_H
