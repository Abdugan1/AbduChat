#include "slidingstackedwidget.h"

SlidingStackedWidget::SlidingStackedWidget(QWidget *parent)
    : QStackedWidget{parent}
{
}

void SlidingStackedWidget::setVerticalMode(bool vertical) {
    vertical_ = vertical;
}

void SlidingStackedWidget::setSlidingSpeed(int speed) {
    slideSpeed_ = speed;
}

void SlidingStackedWidget::setAnimation(enum QEasingCurve::Type animationtype) {
    m_animationtype = animationtype;
}

void SlidingStackedWidget::setWrapMode(bool wrap) {
    wrap_ = wrap;
}

void SlidingStackedWidget::slideNext() {
    int now = currentIndex();
    if (wrap_ || (now < count() - 1))
        slideToIndex(now + 1);
}

void SlidingStackedWidget::slidePrev() {
    int now = currentIndex();
    if (wrap_ || (now > 0))
        slideToIndex(now - 1);
}

void SlidingStackedWidget::slideToIndex(int index, Direction direction) {
    if (index > count() - 1) {
        direction = vertical_ ? TopToBottom : RightToLeft;
        index = (index) % count();
    }
    else if (index < 0) {
        direction = vertical_ ? BottomToTop: LeftToRight;
        index = (index + count()) % count();
    }
    slideToWidget(widget(index), direction);
}

void SlidingStackedWidget::slideToWidget(QWidget * toSlide, Direction direction) {
    if (animationOnProgress_)
        return;

    animationOnProgress_ = true;

    Direction directionhint;
    const int now = currentIndex();
    const int next = indexOf(toSlide);
    if (now == next) {
        animationOnProgress_ = false;
        return;
    }

    if (now < next) {
        directionhint = vertical_ ? TopToBottom : RightToLeft;
    } else {
        directionhint = vertical_ ? BottomToTop : LeftToRight;
    }

    if (direction == Automatic)
        direction = directionhint;

    int offsetx = frameRect().width();
    int offsety = frameRect().height();

    widget(next)->setGeometry(0, 0, offsetx, offsety);

    if (direction == BottomToTop) {
        offsetx = 0;
        offsety = -offsety;
    }
    else if (direction == TopToBottom) {
        offsetx = 0;
        // offsety = offsety;
    }
    else if (direction == RightToLeft) {
        offsetx = -offsetx;
        offsety = 0;
    }
    else if (direction == LeftToRight) {
        // offsetx = offsetx;
        offsety = 0;
    }

    const QPoint pnext = widget(next)->pos();
    const QPoint pnow = widget(now)->pos();
    nowPos_ = pnow;

    nextIndex_ = next;
    nowIndex_ = now;

    widget(next)->move(pnext.x() - offsetx, pnext.y() - offsety);
    // make it visible/show
    widget(next)->show();
    widget(next)->raise();

    QPropertyAnimation *animnow = new QPropertyAnimation(widget(now), "pos");
    animnow->setDuration(slideSpeed_);
    animnow->setEasingCurve(m_animationtype);
    animnow->setStartValue(QPoint(pnow.x(), pnow.y()));
    animnow->setEndValue(QPoint(offsetx + pnow.x(), offsety + pnow.y()));

    QPropertyAnimation *animnext = new QPropertyAnimation(widget(next), "pos");
    animnext->setDuration(slideSpeed_);
    animnext->setEasingCurve(m_animationtype);
    animnext->setStartValue(QPoint(-offsetx + pnext.x(), offsety + pnext.y()));   // Bug: in vertical mode offsety must be -offsety !!!
    animnext->setEndValue(QPoint(pnext.x(), pnext.y()));

    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;

    animgroup->addAnimation(animnow);
    animgroup->addAnimation(animnext);

    connect(animgroup, &QParallelAnimationGroup::finished ,this, &SlidingStackedWidget::animationDoneSlot);
//    connect(animnow, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
//        qDebug() << "now value:" << value;
//        qDebug() << "now pos:" << widget(now)->pos();
//        qDebug() << "\n";
//    });
//    connect(animnext, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
//        qDebug() << "next value:" << value;
//        qDebug() << "next pos:" << widget(next)->pos();
//        qDebug() << "\n";
//    });

    animationOnProgress_ = true;
    animgroup->start();
}

void SlidingStackedWidget::animationDoneSlot(void) {
    setCurrentIndex(nextIndex_);
    widget(nowIndex_)->move(nowPos_);

    animationOnProgress_ = false;

    sender()->deleteLater();

    emit animationFinished();
}
