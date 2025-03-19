#include "qxwrite.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QxWrite window;
    window.show();
    return app.exec();
}
