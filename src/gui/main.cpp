#include <QApplication>
#include "include/gui/mainwindow.h"

#include <QMutex>
#include <QDateTime>

#include <ctime>
#include <iostream>

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message)
{
    static QMutex mutex;
    QMutexLocker lock(&mutex);
    auto time = std::time(nullptr);
    QDateTime dateTime = QDateTime::fromTime_t(time);
    std::cout << dateTime.toString().toStdString() << " -- " << qPrintable(qFormatLogMessage(type, context, message)) << std::endl;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qInstallMessageHandler(messageHandler);

    MainWindow w;
    w.show();

    return app.exec();
}
