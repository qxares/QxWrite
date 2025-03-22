#include "mouseeventhandler.h"
#include <QDebug>

MouseEventHandler::MouseEventHandler(ImageSceneManager *sceneManager, ImageResizer *resizer, QObject *parent)
    : QObject(parent), sceneManager(sceneManager), resizer(resizer), resizing(false) {}

bool MouseEventHandler::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton && resizing) {
            return true; // Start drag handled by ImageResizer
        }
    } else if (event->type() == QEvent::MouseMove && resizing) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->buttons() & Qt::LeftButton) {
            resizer->updateResizing(mouseEvent->pos());
            qDebug() << "Mouse move resizing at" << mouseEvent->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease && resizing) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            resizer->finishResizing();
            resizing = false;
            qDebug() << "Resize drag finished";
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}
