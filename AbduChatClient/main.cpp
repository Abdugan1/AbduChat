#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QTimer>
#include <QDebug>

#include <AbduChatLib/contactstable.h>
#include <AbduChatLib/messagestable.h>
#include <AbduChatLib/connect_to_database.h>

#include "chatclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    connectToDatabase();

    qmlRegisterType<ContactsTable>("AbduChatLib", 1, 0, "ContactsTable");
    qmlRegisterType<MessagesTable>("AbduChatLib", 1, 0, "MessagesTable");

    qmlRegisterType<ChatClient>("AbduChatClient", 1, 0, "ChatClient");

    QQmlApplicationEngine engine;
    QQmlComponent qmlComponent(&engine, QUrl("qrc:/main.qml"));

    QObject* object = qmlComponent.create();

    return app.exec();
}
