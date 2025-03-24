#include "imagescenemanager.h"
#include <QGraphicsPixmapItem>
#include <QDebug>

ImageSceneManager::ImageSceneManager(QObject *parent)
    : QObject(parent), m_scene(new QGraphicsScene(this)) {
    qDebug() << "ImageSceneManager initialized";
}

void ImageSceneManager::addImage(const QUrl &url, const QPixmap &pixmap, int position) {
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
    item->setData(0, url); // Store URL for reference
    item->setPos(position * 10, 0); // Simple mapping, adjust as needed
    m_scene->addItem(item);
    qDebug() << "Added image to scene at position:" << position;
}
