#ifndef CONTEXTMENUHANDLER_H
#define CONTEXTMENUHANDLER_H

#include <QObject>
#include <QPoint>
#include "imagescenemanager.h"
#include "imageresizer.h"
#include "imageselector.h"

class ContextMenuHandler : public QObject {
    Q_OBJECT
public:
    ContextMenuHandler(ImageSceneManager *sceneManager, ImageResizer *resizer, ImageSelector *selector, QWidget *parent = nullptr);
    void showContextMenu(const QPoint &pos);

private:
    ImageSceneManager *sceneManager;
    ImageResizer *resizer;
    ImageSelector *selector;
    QWidget *parentWidget;

private slots:
    void insertImage();
};

#endif // CONTEXTMENUHANDLER_H
