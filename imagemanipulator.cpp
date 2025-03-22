#include "imagemanipulator.h"
#include <QInputDialog>
#include <QDebug>

ImageManipulator::ImageManipulator(ImageSceneManager *sceneManager, ImageResizer *resizer, ImageSelector *selector, QWidget *parent)
    : QObject(parent), sceneManager(sceneManager), resizer(resizer), selector(selector), parentWidget(parent) {}

void ImageManipulator::moveImage() {
    QMap<QUrl, QGraphicsPixmapItem*> imageMap = sceneManager->getImageUrls();
    QList<QUrl> urls = imageMap.keys();
    QUrl selectedUrl = selectImageFromDialog(urls);
    if (selectedUrl.isEmpty()) return;

    bool ok;
    int x = QInputDialog::getInt(parentWidget, tr("Move Image"), tr("New X position:"), 0, -1000, 1000, 1, &ok);
    if (!ok) return;
    int y = QInputDialog::getInt(parentWidget, tr("Move Image"), tr("New Y position:"), 0, -1000, 1000, 1, &ok);
    if (!ok) return;

    if (QGraphicsPixmapItem *item = sceneManager->getImageItem(selectedUrl)) {
        item->setPos(x, y);
        qDebug() << "Moved image" << selectedUrl << "to" << QPoint(x, y);
    }
}

void ImageManipulator::resizeImage() {
    QMap<QUrl, QGraphicsPixmapItem*> imageMap = sceneManager->getImageUrls();
    QList<QUrl> urls = imageMap.keys();
    QUrl selectedUrl = selectImageFromDialog(urls);
    if (selectedUrl.isEmpty()) return;

    bool ok;
    int width = QInputDialog::getInt(parentWidget, tr("Resize Image"), tr("New width:"), 200, 1, 2000, 1, &ok);
    if (!ok) return;
    int height = QInputDialog::getInt(parentWidget, tr("Resize Image"), tr("New height:"), 300, 1, 2000, 1, &ok);
    if (!ok) return;

    if (QGraphicsPixmapItem *item = sceneManager->getImageItem(selectedUrl)) {
        QPixmap scaledPixmap = item->pixmap().scaled(width, height, Qt::KeepAspectRatio);
        sceneManager->updateImage(selectedUrl, scaledPixmap);
        qDebug() << "Resized image" << selectedUrl << "to" << QSize(width, height);
    }
}

QUrl ImageManipulator::selectImageFromDialog(const QList<QUrl> &urls) {
    if (urls.isEmpty()) return QUrl();
    QStringList items;
    for (const QUrl &url : urls) items << url.toString();
    bool ok;
    QString item = QInputDialog::getItem(parentWidget, tr("Select Image"), tr("Choose an image:"), items, 0, false, &ok);
    return ok ? QUrl(item) : QUrl();
}
