#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>

class Label;
class QPropertyAnimation;

class LineEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QColor borderColor WRITE setBorderColor)
public:
    explicit LineEdit( QWidget* parent = nullptr);

    void setValidator(const QValidator* validator);

    void setLeftPixmap(const QPixmap& icon);
    void setRightPixmap(const QPixmap& icon);

    void setLeftPixmapClickable(bool on);
    void setRightPixmapClickable(bool on);

    Label *leftPixmap() const;
    Label *rightPixmap() const;

    void setBorderColor(const QColor& color);

protected:
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    void makeBorderRed();

private:
    Label* leftPixmap_  = nullptr;
    Label* rightPixmap_ = nullptr;

    QPropertyAnimation* borderColorAnimation_ = nullptr;
};

#endif // LINEEDIT_H
