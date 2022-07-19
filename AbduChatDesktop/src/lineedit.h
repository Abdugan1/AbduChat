#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>

class Label;

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEdit( QWidget* parent = nullptr);

    void setValidator(const QValidator* validator);

    void setLeftPixmap(const QPixmap& icon);
    void setRightPixmap(const QPixmap& icon);

    void setLeftPixmapClickable(bool on);
    void setRightPixmapClickable(bool on);

    Label *leftPixmap() const;
    Label *rightPixmap() const;

private:
    Label* leftPixmap_  = nullptr;
    Label* rightPixmap_ = nullptr;
};

#endif // LINEEDIT_H
