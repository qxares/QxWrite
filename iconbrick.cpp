#include "iconbrick.h"
#include <QIcon>
#include <QDebug>

IconBrick::IconBrick(QObject *parent) : QObject(parent) {
    qDebug() << "IconBrick initialized";
}

QIcon IconBrick::getIcon(const QString &name) {
    QString path = ":/icons/icons/" + name + ".png";  // Fixed to match icons.qrc
    QIcon icon(path);
    if (icon.isNull()) {
        qDebug() << "Icon not found:" << path;
    } else {
        qDebug() << "Loaded icon:" << path;
    }
    return icon;
}
