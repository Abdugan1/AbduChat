#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QTimer>
#include <QDebug>

#include <AbduChatLib/userstable.h>
#include <AbduChatLib/chatstable.h>
#include <AbduChatLib/chatsviewtable.h>
#include <AbduChatLib/messagestable.h>
#include <AbduChatLib/sqldatabaseclient.h>

#include "chatclient.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(images);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    SqlDatabaseClient database;
    ChatClient chatClient(&database);

//    qmlRegisterType<User>("AbduChatLib", 1, 0, "User");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("chatClient", &chatClient);
    engine.rootContext()->setContextProperty("usersTable", database.usersTable());
    engine.rootContext()->setContextProperty("chatsTable", database.chatsTable());
    engine.rootContext()->setContextProperty("chatsViewTable", database.chatsViewTable());
    engine.load("qrc:/qml/main.qml");

    return app.exec();
}
