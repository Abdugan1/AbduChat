#include <QApplication>
#include <QFontDatabase>
#include <QFile>
#include <QDebug>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/Montserrat-Regular.ttf");

    QFile qssFile(":/qss/style.qss");
    qssFile.open(QFile::ReadOnly);
    app.setStyleSheet(QLatin1String(qssFile.readAll()));

    app.setFont(QFont("Montserrat"));

    MainWindow window;
    window.show();

    return app.exec();
}
