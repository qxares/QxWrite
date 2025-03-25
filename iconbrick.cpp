#include "iconbrick.h"
#include <QDebug>

IconBrick::IconBrick(QObject *parent) : QObject(parent) {
    qDebug() << "IconBrick initialized";
}

void IconBrick::registerIcons() {
    iconMap["new"] = ":/icons/icons/file-plus.svg";
    iconMap["open"] = ":/icons/icons/open.svg";
    iconMap["save"] = ":/icons/icons/save.svg";
    iconMap["bold"] = ":/icons/icons/bold.svg";
    iconMap["italic"] = ":/icons/icons/italic.svg";
    iconMap["font"] = ":/icons/icons/font.svg";
    iconMap["color"] = ":/icons/icons/color.svg";
    iconMap["image"] = ":/icons/icons/image.svg";
    iconMap["align-left"] = ":/icons/icons/align-left.svg";
    iconMap["align-center"] = ":/icons/icons/align-center.svg";
    iconMap["align-right"] = ":/icons/icons/align-right.svg";

    qDebug() << "IconBrick: Registered" << iconMap.size() << "icons";
}

QIcon IconBrick::getIcon(const QString &name) {
    QIcon icon(iconMap.value(name));
    qDebug() << "IconBrick: Loaded icon:" << name << "from" << iconMap.value(name) << ", sizes:" << icon.availableSizes();
    return icon;
}
