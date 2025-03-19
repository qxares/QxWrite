#ifndef IMAGESCENEMANAGER_H
#define IMAGESCENEMANAGER_H

#include <QObject>
#include <QGraphicsScene>
#include <QUrl>
#include <QPixmap>

class ImageSceneManager : public QObject {
    Q_OBJECT
public:
    explicit ImageSceneManager(QObject *parent = nullptr);
    void addImage(const QUrl &url, const QPixmap &pixmap, int position); // Changed to int for text position
    QGraphicsScene* scene() { return m_scene; }

private:
    QGraphicsScene *m_scene;
};

#endif // IMAGESCENEMANAGER_H
