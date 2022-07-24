#include "chatdelegate.h"

#include <AbduChatLib/database_names.h>

#include <QPainter>
#include <QDateTime>
#include <QMouseEvent>
#include <QDebug>

namespace fieldnames = db::chats_view::fieldnames;
namespace fieldnums = db::chats_view::fieldnums;

const QMargins ChatDelegate::Padding_ = QMargins(7, 7, 7, 7);
const int ChatDelegate::SpacingBetweenAvatarAndText_ = 5;

ChatDelegate::ChatDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
    , avatar_(":/images/avatar_64.png")
{
    avatar_ = avatar_.scaled(48, 48, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

void ChatDelegate::paint(QPainter *painter,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    painter->save();

    drawBackgrouond(painter, option, index);
    drawAvatar(painter, option, index);
    drawText(painter, option, index);

    painter->restore();
}

QSize ChatDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &) const
{
    return QSize(option.rect.width(), avatar_.height() + Padding_.top() + Padding_.bottom());
}

void ChatDelegate::drawBackgrouond(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    painter->setPen(Qt::NoPen);
    if (option.state & QStyle::State_Selected) {
        painter->setBrush(QBrush(QColor(0x41, 0x9f, 0xd9)));
    } else {
        painter->setBrush(QBrush(option.state & QStyle::State_MouseOver ? qRgb(240, 240, 240)
                                                                        : qRgb(255, 255, 255)));
    }
    painter->drawRect(option.rect);

    painter->restore();
}

void ChatDelegate::drawAvatar(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    painter->save();

    painter->drawPixmap(option.rect.x() + Padding_.left(), option.rect.y() + Padding_.top(), avatar_);

    painter->restore();
}

void ChatDelegate::drawText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    if (option.state & QStyle::State_Selected)
        painter->setPen(QPen(Qt::white));

    drawChatUsername(painter, option, index);
    drawLastMessage(painter, option, index);
    drawTimestamp(painter, option, index);

    painter->restore();
}

void ChatDelegate::drawChatUsername(QPainter *painter,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    painter->save();

    const QString chatUsername = getData(index, fieldnums::User2Username).toString();

    QFont font = painter->font();
    font.setPointSize(11);
    font.setBold(true);
    QFontMetrics fontMetrics(font);

    QRect rect = getTextBoundingRect(option.rect);
    painter->setFont(font);
    painter->drawText(rect.x(), rect.y() + fontMetrics.height(), chatUsername);

    painter->restore();
}

void ChatDelegate::drawLastMessage(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const QString lastMessage = getData(index, fieldnums::LastMessage).toString();

    QFont font = painter->font();
    font.setPointSize(10);
    QFontMetrics fontMetrics(font);

    const int width = getTextBoundingRect(option.rect).width() - 20;

    const QString elidedText = fontMetrics.elidedText(lastMessage, Qt::ElideRight, width);

    QRect rect = getTextBoundingRect(option.rect);
    painter->setFont(font);
    painter->drawText(rect.x(), rect.y() + option.rect.height() * 0.7, elidedText);

    painter->restore();
}

void ChatDelegate::drawTimestamp(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const QDateTime date = QDateTime::fromString(getData(index, fieldnums::Date).toString(), Qt::ISODate);
    const QDateTime today = QDateTime::currentDateTime();

    QString timestamp;
    if (date.date().year() != today.date().year()) {
        timestamp = date.toString("dd.MM.yy");
    } else if (date.date().day() == today.date().day()
               && date.date().month() == today.date().month()) {
        timestamp = date.toString("hh:mm");
    } else if (date.daysTo(today) <= 7) {
        timestamp = date.toString("ddd");
    } else if (date.date().year() == today.date().year()) {
        timestamp = date.toString();
    }

    QFont font = painter->font();
    font.setPointSize(10);
    QFontMetrics fontMetrics(font);

    QRect rect = getTextBoundingRect(option.rect);
    painter->setFont(font);
    painter->drawText(rect.x() + getTextBoundingRect(option.rect).width() - fontMetrics.horizontalAdvance(timestamp),
                      rect.y() + fontMetrics.height(),
                      timestamp);

    painter->restore();
}

QRect ChatDelegate::getTextBoundingRect(const QRect &optionRect) const
{
    return QRect{optionRect.x() + Padding_.left() + avatar_.width() + SpacingBetweenAvatarAndText_,
                 optionRect.y() + Padding_.top(),
                 optionRect.width() - Padding_.left() - avatar_.width() - SpacingBetweenAvatarAndText_ - Padding_.right(),
                 optionRect.height() - Padding_.top() - Padding_.bottom()};
}

