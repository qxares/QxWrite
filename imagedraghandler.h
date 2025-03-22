#ifndef IMAGEDRAGHANDLER_H
#define IMAGEDRAGHANDLER_H

#include <QObject>
#include <QMouseEvent>
#include "imagescenemanager.h"

class ImageDragHandler : public QObject {
    Q_OBJECT
public:
    ImageDragHandler(ImageSceneManager *sceneManager, QObject *parent = nullptr);
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    ImageSceneManager *sceneManager;
    QGraphicsPixmapItem *draggedItem;
    QPoint lastPos;
    bool dragging;
};

#endif // IMAGEDRAGHANDLER_H
