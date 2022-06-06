#include <QCoreApplication>
#include <QThreadPool>
#include <QMutex>

#include "console.h"
#include "chatserver.h"
#include <AbduChatLib/connect_to_database.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    connectToDatabase();

    QMutex serverLogsMutex;

    ChatServer chatServer(&serverLogsMutex);

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
