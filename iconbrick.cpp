#include "iconbrick.h"
#include <QDebug>
#include <QPixmap>

IconBrick::IconBrick(QObject *parent) : QObject(parent), fallbackIcon(QIcon(":/icons/icons/bold.svg")) {
    qDebug() << "IconBrick initialized";
    registerIcons();
}

void IconBrick::registerIcons() {
    iconMap["new"] = ":/icons/icons/file-plus.svg";
    iconMap["open"] = ":/icons/icons/open.svg";
    iconMap["save"] = ":/icons/icons/save.svg";
    iconMap["bold"] = ":/icons/icons/bold.svg";
    iconMap["italic"] = ":/icons/icons/italic.svg";
    iconMap["font"] = ":/icons/icons/font.svg";
    iconMap["image"] = ":/icons/icons/image.svg";
    iconMap["color"] = ":/icons/icons/color.svg";
    iconMap["test-color"] = ":/icons/icons/eye-dropper.svg";
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
    QList<QSize> sizes = icon.availableSizes();
    qDebug() << "IconBrick: Loaded icon:" << name << "from" << path << ", sizes:" << sizes;
    return icon;
}

