#ifndef MESSAGEDELEGATE_H
#define MESSAGEDELEGATE_H

#include <QAbstractItemDelegate>

class MessageDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit MessageDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    void drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawMessageText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawTimestamp(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize getTextSize(const QModelIndex &index) const;
    QSize getTimestampSize(const QModelIndex &index) const;
    QSize getAppropriateSize(const QModelIndex &index) const;

private:

    static const int MaxWidth_;
    static const QMargins Padding_;
    QFont TextFont_;
    QFont TimestampFont_;
};

#endif // MESSAGEDELEGATE_H
