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

#include <AbduChatClient/chatclient.h>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(images);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<User>("AbduChatLib", 1, 0, "User");
    qmlRegisterType<Chat>("AbduChatLib", 1, 0, "Chat");
    qmlRegisterType<Message>("AbduChatLib", 1, 0, "Message");

    QQmlApplicationEngine engine;
    engine.setObjectOwnership(ChatClient::instance().user(), QQmlEngine::CppOwnership);
    engine.rootContext()->setContextProperty("chatClient", &ChatClient::instance());
    engine.rootContext()->setContextProperty("database", &SqlDatabaseClient::instance());
    engine.rootContext()->setContextProperty("usersTable", SqlDatabaseClient::instance().usersTable());
    engine.rootContext()->setContextProperty("chatsTable", SqlDatabaseClient::instance().chatsTable());
    engine.rootContext()->setContextProperty("chatsViewTable", SqlDatabaseClient::instance().chatsViewTable());
    engine.rootContext()->setContextProperty("messagesTable", SqlDatabaseClient::instance().messagesTable());
    engine.load("qrc:/qml/main.qml");

    return app.exec();
}
