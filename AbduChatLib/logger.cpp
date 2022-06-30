#include "logger.h"
#include <QFile>
#include <QDateTime>
#include <QtDebug>

QFile Logger::logFile_;
const QString Logger::LogFilename_("logs.txt");


Logger::Logger()
{
}

void Logger::setupLogFile()
{
    logFile_.setFileName(LogFilename_);
    if (!logFile_.open(QFile::Append | QFile::Text))
        qWarning("Cannot open logs file");
}

void Logger::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message)
{
    QTextStream out(&logFile_);
    out << "[" << QDateTime::currentDateTime().toString(Qt::ISODate) << "] ";

    switch (type) {
    case QtInfoMsg:     out << "INF "; break;
    case QtDebugMsg:    out << "DBG "; break;
    case QtWarningMsg:  out << "WRN "; break;
    case QtCriticalMsg: out << "CRT "; break;
    case QtFatalMsg:    out << "FTL "; break;
    }

    out << context.category << ": " << message << "\n";
    out.flush();
}

void Logger::init()
{
    setupLogFile();
    qInstallMessageHandler(messageHandler);
}

void Logger::debug(const QString &message)
{
    qDebug() << message;
}

void Logger::info(const QString &message)
{
    qInfo() << message;
}

void Logger::warning(const QString &message)
{
    qWarning() << message;
}

void Logger::critical(const QString &message)
{
    qCritical() << message;
}

void Logger::fatal(const QString &message)
{
    qFatal(qPrintable(message));
}
