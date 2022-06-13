#ifndef SERVERLOGSWINDOW_H
#define SERVERLOGSWINDOW_H

#include <ncurses.h>
#include <QString>

class ServerLogsWindow
{
public:
    explicit ServerLogsWindow(int physicalYPos, int physicalXPos, int height, int width);

    WINDOW *pad() const;

    int rows() const;
    void setRows(int newRows);

    int cols() const;
    void setCols(int newCols);


    void refreshPrintYPos();
    void saveEndYPos();
    void print(const QString& str);

    void scrollUp();
    void scrollDown();

    void scrollToBegin();
    void scrollToEnd();

    void refresh();

private:
    void createNewPad();

private:
    WINDOW* pad_ = nullptr;

    int rows_ = 32;
    int cols_ = 0;

    int height_ = 0;
    int width_  = 0;

    int xStart_ = 0;
    int yStart_ = 0;

    int physicalYPos_ = 0;
    int physicalXPos_ = 0;

    int printY_ = 0;
    int endY_ = 0;
};

#endif // SERVERLOGSWINDOW_H
