#include "messagedelegate.h"

#include <AbduChatLib/database_names.h>

#include <QDateTime>
#include <QPainter>
#include <QApplication>
#include <QDebug>

const int MessageDelegate::MaxWidth_ = 300;
const QMargins MessageDelegate::Padding_ = QMargins{15, 10, 15, 0};

namespace fieldnums = db::messages::fieldnums;

MessageDelegate::MessageDelegate(QObject *parent)
    : QAbstractItemDelegate{parent}
{
    TextFont_.setPointSize(11);
    TimestampFont_.setPointSize(10);
}

void MessageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    painter->translate(option.rect.width() - getAppropriateSize(index).width(), 0);

    drawBackground(painter, option, index); // #3879B3
    drawMessageText(painter, option, index);
    drawTimestamp(painter, option, index);

    painter->restore();
}

QSize MessageDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return getAppropriateSize(index);
}

void MessageDelegate::drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);

    // 0x41, 0x9f, 0xd9
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush{QColor{0x38, 0x79, 0xb3}});
    painter->drawRoundedRect(QRect(option.rect.topLeft(), getAppropriateSize(index)), 10, 10);

    painter->restore();
}

void MessageDelegate::drawMessageText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const QString text = getData(index, fieldnums::Text).toString();

    painter->translate(Padding_.left(), Padding_.top());
    painter->setFont(TextFont_);
    painter->setPen(QColor{Qt::white});

    QRect textRect(option.rect.topLeft(), getTextSize(index));
//    painter->drawRect(textRect);
    painter->drawText(textRect, Qt::TextWordWrap, text);

    painter->restore();
}

void MessageDelegate::drawTimestamp(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const QString timestamp = QDateTime::fromString(getData(index, fieldnums::Date).toString(), Qt::ISODate)
                                        .toString("hh:mm");

    QRect textRect(option.rect.topLeft(), getTextSize(index));
    QRect timestampRect = QRect{QPoint{0, 0}, getTimestampSize(index)};


    QPoint translatePoint{textRect.right() + Padding_.left(), textRect.bottom()};
    painter->translate(translatePoint);
    painter->setFont(TimestampFont_);
    painter->setPen(QColor{Qt::white});

//    painter->drawRect(timestampRect);
    painter->drawText(0, timestampRect.height(), timestamp);

    painter->restore();
}

QSize MessageDelegate::getTextSize(const QModelIndex &index) const
{
    const QString text = getData(index, fieldnums::Text).toString();
    QRect rect = QRect(0, 0, MaxWidth_, 1000) - Padding_;
    QRect textRect = QFontMetrics(TextFont_).boundingRect(rect, Qt::TextWordWrap, text);

    return textRect.size();
}

QSize MessageDelegate::getTimestampSize(const QModelIndex &index) const
{
    const QString timestamp = QDateTime::fromString(getData(index, fieldnums::Date).toString(), Qt::ISODate)
                                        .toString("hh:mm");
    QRect timestampRect = QFontMetrics(TimestampFont_).boundingRect(timestamp);

    return timestampRect.size();
}

QSize MessageDelegate::getAppropriateSize(const QModelIndex &index) const
{
    QSize size = getTextSize(index) + getTimestampSize(index);
    size.setWidth(size.width() + Padding_.left() + Padding_.right());
    size.setHeight(size.height() + Padding_.top() + Padding_.bottom());
    return size;
}
