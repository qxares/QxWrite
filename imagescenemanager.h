#ifndef IMAGESCENEMANAGER_H
#define IMAGESCENEMANAGER_H

#include <QObject>
#include <QGraphicsScene>
#include <QUrl>
#include <QPixmap>
#include <QMap>

class ImageSceneManager : public QObject {
    Q_OBJECT
public:
    explicit ImageSceneManager(QObject *parent = nullptr);
    void addImage(const QUrl &url, const QPixmap &pixmap, int position); // Changed to int for text position
    QGraphicsScene* scene() { return m_scene; }
    QGraphicsItem* itemAt(const QPoint &pos); // New method to find item at position
    QMap<QGraphicsPixmapItem*, QUrl> getImageUrls() const { return m_imageUrls; } // New method to get URL map

private:
    QGraphicsScene *m_scene;
    QMap<QGraphicsPixmapItem*, QUrl> m_imageUrls; // Track pixmap items to URLs
};

#endif // IMAGESCENEMANAGER_H
