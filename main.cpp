#include <QApplication>
#include <QDebug>
#include "mainwindowbrick.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindowBrick window;
    window.show();
    qDebug() << "Starting event loop";
    int result = app.exec();
    qDebug() << "Exiting main with result:" << result;
    return result;
}
