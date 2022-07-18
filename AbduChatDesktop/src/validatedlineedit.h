#ifndef VALIDATEDLINEEDIT_H
#define VALIDATEDLINEEDIT_H

#include <QLineEdit>

class QLabel;

class ValidatedLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit ValidatedLineEdit( QWidget* parent = nullptr);

    void setValidator(const QValidator* validator);
    void setIcon(const QPixmap& icon);

private:
    QLabel* iconLabel_ = nullptr;
};

#endif // VALIDATEDLINEEDIT_H
