#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QRunnable>

typedef struct _win_st WINDOW;

class ServerLogsTable;
class ServerLogsWindow;

class QMutex;

enum Pages {
    MainMenu,
    ServerLogs,
};

class Console : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Console(QMutex* serverLogsMutex);
    ~Console();

    void run() override;

    void setServerLogsTable(ServerLogsTable *newServerLogsTable);

signals:
    void startServer();
    void stopServer();

    void quitApp();

private:
    void printCurrentPage();

    // MainMenu
    void printMainMenu();
    void parseMainMenuChoice(char choice);

    void toggleServerEnable();
    void quit();

    // ServerLogs
    void printServerLogs();

private:
    bool run_ = true;
    bool serverEnabled_ = false;
    std::string ipAddress_;

    int initialWidth_ = 0;
    int initialHeight_ = 0;

    int windowHeight_ = 0;
    int windowWidth_  = 0;

    Pages currentPage_ = MainMenu;
    WINDOW* headerWindow_  = nullptr;
    WINDOW* contentWindow_ = nullptr;
    ServerLogsWindow* serverLogsPad_ = nullptr;

    ServerLogsTable* serverLogsTable_ = nullptr;
    QMutex* serverLogsMutex_ = nullptr;

    int padHeight_ = 32;
};

#endif // CONSOLE_H
