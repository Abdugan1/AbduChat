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
#include <AbduChatLib/user.h>
#include <AbduChatLib/chat.h>
#include <AbduChatLib/message.h>
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

    qmlRegisterType<User>("AbduChatLib", 1, 0, "User");
    qmlRegisterType<Chat>("AbduChatLib", 1, 0, "Chat");
    qmlRegisterType<Message>("AbduChatLib", 1, 0, "Message");

    QQmlApplicationEngine engine;
    engine.setObjectOwnership(chatClient.user(), QQmlEngine::CppOwnership);
    engine.rootContext()->setContextProperty("chatClient", &chatClient);
    engine.rootContext()->setContextProperty("database", &database);
    engine.rootContext()->setContextProperty("usersTable", database.usersTable());
    engine.rootContext()->setContextProperty("chatsTable", database.chatsTable());
    engine.rootContext()->setContextProperty("chatsViewTable", database.chatsViewTable());
    engine.rootContext()->setContextProperty("messagesTable", database.messagesTable());
    engine.load("qrc:/qml/main.qml");

    return app.exec();
}
