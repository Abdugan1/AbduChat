#ifndef LOGGER_H
#define LOGGER_H

#include <QLoggingCategory>
#include <QFile>

class Logger
{
public:
    static void init();

    static void debug(const QString& message);
    static void info(const QString& message);
    static void warning(const QString& message);
    static void critical(const QString& message);
    static void fatal(const QString& message);

private:
    explicit Logger();
    static void setupLogFile();

    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message);

private:
    static QFile logFile_;
    static const QString LogFilename_;
};

#endif // LOGGER_H
