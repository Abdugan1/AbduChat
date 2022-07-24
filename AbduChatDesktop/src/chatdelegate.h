#ifndef CHATDELEGATE_H
#define CHATDELEGATE_H

#include <QAbstractItemDelegate>

class ChatDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit ChatDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    void drawBackgrouond(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void drawAvatar(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void drawText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void drawChatUsername(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void drawLastMessage(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void drawTimestamp(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QRect getTextBoundingRect(const QRect& optionRect) const;

private:
    QPixmap avatar_;

    static const QMargins Padding_;
    static const int SpacingBetweenAvatarAndText_;
};

#endif // CHATDELEGATE_H
