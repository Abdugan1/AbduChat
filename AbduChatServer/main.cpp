#include <QCoreApplication>
#include <QThreadPool>
#include <QMutex>

#include "console.h"
#include "chatserver.h"
#include <AbduChatLib/sqldatabaseserver.h>
#include <AbduChatLib/user.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    SqlDatabaseServer database;

    QMutex serverLogsMutex;

    ChatServer chatServer(&database, &serverLogsMutex);

    auto threadPool = QThreadPool::globalInstance();

    Console* runnable = new Console(&serverLogsMutex);
    runnable->setAutoDelete(true);
    runnable->setServerLogsTable(chatServer.serverLogsTable());

    threadPool->start(runnable);

    QObject::connect(runnable, &Console::quitApp, &app, &QCoreApplication::quit);

    QObject::connect(runnable, &Console::startServer, &chatServer, &ChatServer::start);
    QObject::connect(runnable, &Console::stopServer, &chatServer, &ChatServer::stop);

    return app.exec();
}
