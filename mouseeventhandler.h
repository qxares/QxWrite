#ifndef MOUSEEVENTHANDLER_H
#define MOUSEEVENTHANDLER_H

#include <QObject>
#include <QMouseEvent>
#include "imagescenemanager.h"
#include "imageresizer.h"

class MouseEventHandler : public QObject {
    Q_OBJECT
public:
    MouseEventHandler(ImageSceneManager *sceneManager, ImageResizer *resizer, QObject *parent = nullptr);
    bool eventFilter(QObject *obj, QEvent *event) override;
    bool resizing; // Public for DocumentEditor to toggle

private:
    ImageSceneManager *sceneManager;
    ImageResizer *resizer;
};

#endif // MOUSEEVENTHANDLER_H
