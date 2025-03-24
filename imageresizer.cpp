#include "imageresizer.h"
#include "imagescenemanager.h"
#include <QDebug>

ImageResizer::ImageResizer(QWidget *parent) 
    : QObject(parent), sceneManager(nullptr), activeItem(nullptr), rubberBand(nullptr) {}

void ImageResizer::setSceneManager(ImageSceneManager *manager) {
    sceneManager = manager;
}

void ImageResizer::startResizing(const QUrl &imageUrl, QGraphicsPixmapItem *item, const QPoint &startPos) {
    activeImageUrl = imageUrl;
    activeItem = item;
    this->startPos = startPos;
    startSize = item->pixmap().size();
    if (!rubberBand) {
        rubberBand = new QRubberBand(QRubberBand::Rectangle, parentWidget());
    }
    rubberBand->setGeometry(QRect(startPos, QSize()));
    rubberBand->show();
    qDebug() << "Starting resize for" << imageUrl << "at" << startPos;
}

void ImageResizer::updateResizing(const QPoint &currentPos) {
    if (!activeItem || !rubberBand) return;
    QRect rect(startPos, currentPos);
    rubberBand->setGeometry(rect.normalized());
}

void ImageResizer::finishResizing() {
    if (!activeItem || !rubberBand || !sceneManager) return;
    QRect rect = rubberBand->geometry();
    QSize newSize = rect.size();
    if (newSize.isValid() && newSize != startSize) {
        QPixmap scaledPixmap = activeItem->pixmap().scaled(newSize, Qt::KeepAspectRatio);
        activeItem->setPixmap(scaledPixmap);
        qDebug() << "Resized image" << activeImageUrl << "to" << newSize;
    }
    rubberBand->hide();
    activeItem = nullptr;
}

QWidget* ImageResizer::parentWidget() const {
    return qobject_cast<QWidget*>(parent());
}
