#ifndef IMAGERESIZER_H
#define IMAGERESIZER_H

#include <QObject>
#include <QUrl>
#include <QPoint>
#include <QRubberBand>
#include <QGraphicsPixmapItem>

class ImageSceneManager;

class ImageResizer : public QObject {
    Q_OBJECT
public:
    ImageResizer(QWidget *parent = nullptr);
    void setSceneManager(ImageSceneManager *manager);
    void startResizing(const QUrl &imageUrl, QGraphicsPixmapItem *item, const QPoint &startPos);
    void updateResizing(const QPoint &currentPos);
    void finishResizing();
    QWidget* parentWidget() const;

private:
    ImageSceneManager *sceneManager;
    QUrl activeImageUrl;
    QGraphicsPixmapItem *activeItem;
    QPoint startPos;
    QSize startSize;
    QRubberBand *rubberBand;
};

#endif // IMAGERESIZER_H
