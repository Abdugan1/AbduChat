#include "serverlogswindow.h"

ServerLogsWindow::ServerLogsWindow(int physicalYPos, int physicalXPos, int height, int width)
{
    physicalYPos_ = physicalYPos;
    physicalXPos_ = physicalXPos;

    height_ = height;
    width_  = width;

    cols_ = width;

    createNewPad();
}

WINDOW *ServerLogsWindow::pad() const
{
    return pad_;
}

int ServerLogsWindow::rows() const
{
    return rows_;
}

void ServerLogsWindow::setRows(int newRows)
{
    rows_ = newRows;
    delwin(pad_);
    createNewPad();
}

int ServerLogsWindow::cols() const
{
    return cols_;
}

void ServerLogsWindow::setCols(int newCols)
{
    cols_ = newCols;
    delwin(pad_);
    createNewPad();
}

void ServerLogsWindow::refreshPrintYPos()
{
    printY_ = 0;
}

void ServerLogsWindow::saveEndYPos()
{
    endY_ = getcury(pad_);
}

void ServerLogsWindow::print(const QString &str)
{
    mvwprintw(pad_, printY_, 0, str.toStdString().c_str());
    printY_ = getcury(pad_) + 1;
}

void ServerLogsWindow::scrollUp()
{
    yStart_ = std::max(0, yStart_ - 1);
}

void ServerLogsWindow::scrollDown()
{
    yStart_ = std::min(rows_ - 1, yStart_ + 1);
    if (getcury(pad_) >= rows_ - 1) {
        setRows(rows_ * 2);
    }
}

void ServerLogsWindow::scrollToBegin()
{
    yStart_ = 0;
}

void ServerLogsWindow::scrollToEnd()
{
    yStart_ = endY_ - height_ + 2;
}

void ServerLogsWindow::refresh()
{
    prefresh(pad_, //pad
             yStart_, // startY
             xStart_,  // startX
             physicalYPos_,  // phisical_y_pos
             physicalXPos_,  // phisical_x_pos
             height_ - 1,  // how many rows after startY. Logic is <=, NOT the <
             width_  - 1  // how many cols after startX. Logic is <=, NOT the <
             );
}

void ServerLogsWindow::createNewPad()
{
    pad_ = newpad(rows_, cols_);
    keypad(pad_, true);
    nodelay(pad_, true);
}
