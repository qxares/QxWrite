#include "iconbrick.h"
#include <QDebug>

IconBrick::IconBrick(QObject *parent) : QObject(parent) {
    qDebug() << "IconBrick initialized";
    iconMap["new"] = ":/icons/icons/file-plus.svg";
    iconMap["open"] = ":/icons/icons/open.svg";
    iconMap["save"] = ":/icons/icons/save.svg";
    iconMap["bold"] = ":/icons/icons/bold.svg";
    iconMap["italic"] = ":/icons/icons/italic.svg";
    iconMap["font"] = ":/icons/icons/font.svg";
    iconMap["color"] = ":/icons/icons/color.svg";
    iconMap["image"] = ":/icons/icons/image.svg";
    qDebug() << "IconBrick: Registered" << iconMap.size() << "icons";
}

QIcon IconBrick::getIcon(const QString &name) {
    if (iconMap.contains(name)) {
        QIcon icon(iconMap[name]);
        qDebug() << "IconBrick: Loaded icon:" << name << "from" << iconMap[name] << ", sizes:" << icon.availableSizes();
        return icon;
    }
    qDebug() << "IconBrick: Icon not found:" << name;
    return QIcon();
}
