#include <QApplication>
#include <QStyleFactory>
#include "mainwindowbrick.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion")); // Set Fusion style for consistent look
    MainWindowBrick window(nullptr); // Explicitly pass nullptr to constructor
    window.show();
    return app.exec();
}
