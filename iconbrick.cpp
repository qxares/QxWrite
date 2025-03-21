#include "iconbrick.h"
#include <QDebug>

IconBrick::IconBrick(QObject *parent) : QObject(parent), fallbackIcon(QIcon(":/icons/icons/bold.png")) {
    qDebug() << "IconBrick initialized";
    registerIcons();
}

void IconBrick::registerIcons() {
    iconMap["new"] = ":/icons/icons/file-plus.png";
    iconMap["open"] = ":/icons/icons/open.png";
    iconMap["save"] = ":/icons/icons/save.png";
    iconMap["bold"] = ":/icons/icons/bold.png";
    iconMap["italic"] = ":/icons/icons/italic.png";
    iconMap["font"] = ":/icons/icons/font.png";
    iconMap["image"] = ":/icons/icons/image.png";
    qDebug() << "IconBrick: Registered" << iconMap.size() << "icons";
}

QIcon IconBrick::loadIcon(const QString &name) {
    QString path = iconMap.value(name, "");
    if (path.isEmpty()) {
        qDebug() << "IconBrick: No icon registered for:" << name << ", using fallback";
        return fallbackIcon;
    }
    QIcon icon(path);
    if (icon.isNull()) {
        qDebug() << "IconBrick: Failed to load icon:" << path << ", using fallback";
        return fallbackIcon;
    }
    qDebug() << "IconBrick: Loaded icon:" << name << "from" << path;
    return icon;
}

