#ifndef CONNECTIONERRORPAGE_H
#define CONNECTIONERRORPAGE_H

#include <QWidget>

class UiConnectionErrorPage;

class ConnectionErrorPage : public QWidget
{
public:
    explicit ConnectionErrorPage(QWidget* parent = nullptr);

private:
    UiConnectionErrorPage* ui_ = nullptr;
};

#endif // CONNECTIONERRORPAGE_H
