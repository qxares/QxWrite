#include "imagedraghandler.h"
#include <QDebug>
#include <QGraphicsView>

ImageDragHandler::ImageDragHandler(ImageSceneManager *sceneManager, QObject *parent)
    : QObject(parent), sceneManager(sceneManager), draggedItem(nullptr), dragging(false) {}

bool ImageDragHandler::eventFilter(QObject *obj, QEvent *event) {
    QGraphicsView *view = qobject_cast<QGraphicsView*>(obj);
    if (!view) return false;

    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            QPointF scenePos = view->mapToScene(mouseEvent->pos());
            QGraphicsItem *item = sceneManager->itemAt(scenePos.toPoint());
            if (item) {
                draggedItem = dynamic_cast<QGraphicsPixmapItem*>(item);
                if (draggedItem) {
                    lastPos = scenePos.toPoint();
                    dragging = true;
                    qDebug() << "Starting drag for item at" << draggedItem->pos();
                    return true;
                }
            }
        }
    } else if (event->type() == QEvent::MouseMove && dragging) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->buttons() & Qt::LeftButton) {
            QPointF scenePos = view->mapToScene(mouseEvent->pos());
            QPoint delta = scenePos.toPoint() - lastPos;
            draggedItem->moveBy(delta.x(), delta.y());
            lastPos = scenePos.toPoint();
            qDebug() << "Dragging to" << draggedItem->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease && dragging) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            dragging = false;
            draggedItem = nullptr;
            qDebug() << "Drag finished";
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}
