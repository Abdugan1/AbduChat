#ifndef LABEL_H
#define LABEL_H

#include <QLabel>

class Label : public QLabel
{
    Q_OBJECT
public:
    explicit Label(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    explicit Label(const QString &text, QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());

    bool clickable() const;
    void setClickable(bool on);

signals:
    void pressed();
    void released();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool clickable_ = false;
};

#endif // LABEL_H
