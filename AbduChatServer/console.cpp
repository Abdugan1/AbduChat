#include "console.h"
#include "chatserver.h"
#include "serverlogswindow.h"

#include <QNetworkInterface>
#include <QSqlRecord>
#include <QMutexLocker>

#include <ncurses.h>

#include <AbduChatLib/serverlogstable.h>
#include <AbduChatLib/database_names.h>

const char* MainMenuHeader = "AbduChatServer";
const char* ServerLogsHeader = "Server Logs";
const int Port = 2002;

std::string getNonLocalIpAddress()
{
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    return ipAddress.toStdString();
}

Console::Console(QMutex* serverLogsMutex)
    : ipAddress_(getNonLocalIpAddress())
    , serverLogsMutex_(serverLogsMutex)
{
    initscr();
    getmaxyx(stdscr, initialHeight_, initialWidth_);

    windowHeight_ = initialHeight_ - 2;
    windowWidth_  = initialWidth_  - 2;

    curs_set(0); // no cursor

    headerWindow_ = newwin(1, initialWidth_, 0, 0);

    contentWindow_ = newwin(windowHeight_, windowWidth_, 1, 1);
    keypad(contentWindow_, true);

    serverLogsPad_ = new ServerLogsWindow(initialHeight_, initialWidth_);
}

Console::~Console()
{
    endwin();
}

void Console::run()
{
    box(stdscr, 0, 0);
    refresh();

    while (run_) {
        printCurrentPage();
    }
}

void Console::printCurrentPage()
{
    switch (currentPage_) {
    case MainMenu:
        printMainMenu();
        break;
    case ServerLogs:
        printServerLogs();
        break;
    }
}

void Console::printMainMenu()
{
    // Info
    mvwprintw(contentWindow_, 0, initialWidth_ / 2 - strlen(MainMenuHeader) / 2, MainMenuHeader);

    WINDOW* infoWindow = subwin(contentWindow_, 5, 25, 2, initialWidth_ - 26);
    box(infoWindow, 0, 0);
    mvwprintw(infoWindow, 1, 2, (std::string("Server enabled: ") + (serverEnabled_ ? "true" : "false")).c_str());
    mvwprintw(infoWindow, 2, 2, ("IP: " + ipAddress_).c_str());
    mvwprintw(infoWindow, 3, 2, ("Port: " + std::to_string(Port)).c_str());
    wrefresh(infoWindow);

    // Options
    const int OptionsCount = 3;
    static const std::string options[OptionsCount] = {
        "Start/Stop server",
        "Server logs",
        "Exit"
    };

    static int choice = 0;
    int r = 4;
    for (int i = 0; i < OptionsCount; ++i) {
        if (i == choice)
            mvwprintw(contentWindow_, r++, 2, ("> " + options[i]).c_str());
        else
            mvwprintw(contentWindow_, r++, 2, ("  " + options[i]).c_str());
    }

    switch (wgetch(contentWindow_)) {
    case KEY_UP:
        choice = std::max(0, --choice);
        break;
    case KEY_DOWN:
        choice = std::min(OptionsCount - 1, ++choice);
        break;
    case 10: // Enter
        parseMainMenuChoice(choice);
        break;
    }

    wrefresh(contentWindow_);
}

void Console::parseMainMenuChoice(char choice)
{
    switch (choice) {
    case 0:
        toggleServerEnable();
        break;
    case 1:
        currentPage_ = ServerLogs;
        wclear(contentWindow_);
        break;
    case 2:
        quit();
        break;
    }
}

void Console::toggleServerEnable()
{
    if (serverEnabled_) {
        emit stopServer();
        serverEnabled_ = false;
    } else {
        emit startServer();
        serverEnabled_ = true;
    }
}

void Console::quit()
{
    run_ = false;
    emit quitApp();
}

void Console::printServerLogs()
{
    namespace FieldNames = db::server_logs::fieldnames;

    QMutexLocker serverLogsLocker(serverLogsMutex_);

    serverLogsPad_->refreshPrintYPos();

    int rowCount = serverLogsTable_->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        QSqlRecord record = serverLogsTable_->record(i);
        QString text = record.value(FieldNames::Text).toString();
        QString insertDatetime = record.value(FieldNames::InsertDatetime).toString();

        QString  log = (insertDatetime + ": " + text + "\n");
        serverLogsPad_->print(log);
    }

    switch (wgetch(serverLogsPad_->pad())) {
    case KEY_UP: {
        serverLogsPad_->scrollUp();
        break;
    }
    case KEY_DOWN:{
        serverLogsPad_->scrollDown();
        break;
    }
    case 'x':
        currentPage_ = MainMenu;
        wclear(serverLogsPad_->pad());
        break;
    }

    serverLogsPad_->refresh();
}

void Console::setServerLogsTable(ServerLogsTable *newServerLogsTable)
{
    serverLogsTable_ = newServerLogsTable;
}
