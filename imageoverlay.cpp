#include "imageoverlay.h"
#include <QDebug>
#include <QMouseEvent>

ImageOverlay::ImageOverlay(QWidget *parent) : QGraphicsView(parent), scene(new QGraphicsScene(this)), rubberBand(nullptr), resizing(false) {
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background: transparent;");
    setMouseTracking(true);
}

void ImageOverlay::addImage(const QUrl &imageUrl, const QPixmap &pixmap, const QPoint &pos) {
    QGraphicsPixmapItem *item = scene->addPixmap(pixmap.scaled(100, 117, Qt::KeepAspectRatio));
    item->setPos(pos);
    images[imageUrl] = item;
    qDebug() << "Added image to overlay:" << imageUrl << "at" << pos;
}

void ImageOverlay::startResizing(const QUrl &imageUrl, const QPoint &startPos) {
    if (!images.contains(imageUrl)) return;
    activeImageUrl = imageUrl;
    this->startPos = mapToScene(startPos).toPoint();
    QGraphicsPixmapItem *item = images[imageUrl];
    startSize = item->pixmap().size();
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    QRect rect(item->pos().toPoint(), startSize);
    rubberBand->setGeometry(rect);
    rubberBand->show();
    setCursor(Qt::SizeFDiagCursor);
    resizing = true;
    qDebug() << "Starting resizing for" << imageUrl << "Start size:" << startSize << "at" << rect;
}

void ImageOverlay::updateResizing(const QPoint ¤tPos) {
    if (activeImageUrl.isEmpty() || !rubberBand) return;
    QPoint currentPos = mapToScene(currentPos).toPoint();
    int deltaX = currentPos.x() - startPos.x();
    int newWidth = qMax(50, startSize.width() + deltaX);
    qreal aspectRatio = static_cast<qreal>(startSize.height()) / startSize.width();
    int newHeight = qMax(50, static_cast<int>(newWidth * aspectRatio));
    int maxWidth = viewport()->width() - images[activeImageUrl]->pos().x();
    newWidth = qMin(newWidth, maxWidth);
    newHeight = qMin(newHeight, static_cast<int>(maxWidth * aspectRatio));

    QRect newRect(images[activeImageUrl]->pos().toPoint(), QSize(newWidth, newHeight));
    rubberBand->setGeometry(newRect);
    images[activeImageUrl]->setPixmap(images[activeImageUrl]->pixmap().scaled(newWidth, newHeight, Qt::KeepAspectRatio));
    qDebug() << "Resizing to" << newWidth << "x" << newHeight;
}

void ImageOverlay::finishResizing() {
    if (!activeImageUrl.isEmpty()) {
        delete rubberBand;
        rubberBand = nullptr;
        activeImageUrl.clear();
        unsetCursor();
        resizing = false;
        qDebug() << "Resizing finished";
    }
}

void ImageOverlay::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && !resizing) {
        QGraphicsItem *item = itemAt(event->pos());
        if (item && images.values().contains(dynamic_cast<QGraphicsPixmapItem*>(item))) {
            QUrl url = images.key(dynamic_cast<QGraphicsPixmapItem*>(item));
            startResizing(url, event->pos());
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void ImageOverlay::mouseMoveEvent(QMouseEvent *event) {
    if (resizing && (event->buttons() & Qt::LeftButton)) {
        updateResizing(event->pos());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void ImageOverlay::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && resizing) {
        finishResizing();
    }
    QGraphicsView::mouseReleaseEvent(event);
}
