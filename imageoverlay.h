#ifndef IMAGEOVERLAY_H
#define IMAGEOVERLAY_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QUrl>
#include <QPoint>
#include <QRubberBand>

class ImageOverlay : public QGraphicsView {
    Q_OBJECT
public:
    ImageOverlay(QWidget *parent = nullptr);
    void addImage(const QUrl &imageUrl, const QPixmap &pixmap, const QPoint &pos);
    void startResizing(const QUrl &imageUrl, const QPoint &startPos);
    void updateResizing(const QPoint &currentPos);
    void finishResizing();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QGraphicsScene *scene;
    QMap<QUrl, QGraphicsPixmapItem*> images;
    QUrl activeImageUrl;
    QPoint startPos;
    QSize startSize;
    QRubberBand *rubberBand;
    bool resizing;
};

#endif // IMAGEOVERLAY_H
