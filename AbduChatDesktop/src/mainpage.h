#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QSplitter>

class UiMainPage;

class MainPage : public QSplitter
{
public:
    explicit MainPage(QWidget* parent = nullptr);

private:
    UiMainPage* ui_ = nullptr;
};

#endif // MAINPAGE_H
