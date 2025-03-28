#include "imageselector.h"
#include "imagescenemanager.h"
#include <QGraphicsPixmapItem> // Added for dynamic_cast
#include <QDebug>

ImageSelector::ImageSelector(QTextEdit *editor, QObject *parent) 
    : QObject(parent), editor(editor), sceneManager(nullptr) {}

void ImageSelector::setSceneManager(ImageSceneManager *manager) {
    sceneManager = manager;
}

QUrl ImageSelector::selectImage(const QPoint &pos) {
    if (!sceneManager) return QUrl();
    QGraphicsItem *item = sceneManager->itemAt(pos);
    if (auto *pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(item)) {
        selectedImageUrl = sceneManager->getImageUrls().value(pixmapItem); // Swapped key() for value()
        qDebug() << "Selected image:" << selectedImageUrl;
        return selectedImageUrl;
    }
    selectedImageUrl = QUrl();
    return QUrl();
}

bool ImageSelector::isImageSelected() const {
    return !selectedImageUrl.isEmpty();
}
