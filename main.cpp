#include "mainwindowbrick.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindowBrick window;
    window.show();
    return app.exec();
}
