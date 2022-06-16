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
#include <AbduChatLib/messagestableclient.h>
#include <AbduChatLib/connect_to_database.h>

#include "chatclient.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(images);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    connectToDatabase();

    qmlRegisterType<UsersTable>("AbduChatLib", 1, 0, "ContactsTable");
    qmlRegisterType<MessagesTableClient>("AbduChatLib", 1, 0, "MessagesTable");

    qmlRegisterType<ChatClient>("AbduChatClient", 1, 0, "ChatClient");

    QQmlApplicationEngine engine;
    QQmlComponent qmlComponent(&engine, QUrl("qrc:/qml/main.qml"));

    QObject* root = qmlComponent.create();

    QObject* chatClient = root->findChild<QObject*>("chatClient");
    QObject* contactsTable = root->findChild<QObject*>("contactsTable");
    QObject* messagesTable = root->findChild<QObject*>("messagesTable");

    QObject::connect(chatClient,    SIGNAL(contactsAvailable(QJsonArray)),
                     contactsTable, SLOT(insertContacts(QJsonArray)));

    QObject::connect(chatClient,    SIGNAL(messageReceived(Message)),
                     messagesTable, SLOT(insertMessage(Message)));
    QObject::connect(chatClient,    SIGNAL(messagesAvailable(QJsonArray)),
                     messagesTable, SLOT(insertMessages(QJsonArray)));

    return app.exec();
}
