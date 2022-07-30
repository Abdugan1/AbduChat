#ifndef SLIDINGSTACKEDWIDGET_H
#define SLIDINGSTACKEDWIDGET_H

#include <QStackedWidget>

#include <QtGui>
#include <QWidget>
#include <QDebug>
#include <QEasingCurve>

class SlidingStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    enum Direction {
        LeftToRight,
        RightToLeft,
        TopToBottom,
        BottomToTop,
        Automatic
    };

    explicit SlidingStackedWidget(QWidget *parent = nullptr);

public slots:
    void setSlidingSpeed(int speed);
    void setAnimation(QEasingCurve::Type animationtype);
    void setVerticalMode(bool vertical = true);
    void setWrapMode(bool wrap);

    void slideNext();
    void slidePrev();
    void slideToIndex(int index, SlidingStackedWidget::Direction direction = Automatic);

signals:
    void animationFinished(void);

protected slots:
    void animationDoneSlot(void);

protected:
    void slideToWidget(QWidget *widget, Direction direction = Automatic);

    int slideSpeed_ = 500;
    QEasingCurve::Type m_animationtype = QEasingCurve::OutCubic;
    bool vertical_ = false;
    int nowIndex_ = 0;
    int nextIndex_ = 0;
    bool wrap_ = false;
    QPoint nowPos_;
    bool animationOnProgress_ = false;
};

#endif // SLIDINGSTACKEDWIDGET_H
