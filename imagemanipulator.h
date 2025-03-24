#ifndef IMAGEMANIPULATOR_H
#define IMAGEMANIPULATOR_H

#include <QObject>
#include <QUrl>
#include "imagescenemanager.h"
#include "imageresizer.h"
#include "imageselector.h"

class ImageManipulator : public QObject {
    Q_OBJECT
public:
    ImageManipulator(ImageSceneManager *sceneManager, ImageResizer *resizer, ImageSelector *selector, QWidget *parent = nullptr);
    void moveImage();
    void resizeImage();

private:
    ImageSceneManager *sceneManager;
    ImageResizer *resizer;
    ImageSelector *selector;
    QWidget *parentWidget;
    QUrl selectImageFromDialog(const QList<QUrl> &urls);
};

#endif // IMAGEMANIPULATOR_H
