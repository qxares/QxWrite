#ifndef IMAGESELECTOR_H
#define IMAGESELECTOR_H

#include <QObject>
#include <QTextEdit>
#include <QUrl>
#include <QPoint>

class ImageSceneManager;

class ImageSelector : public QObject {
    Q_OBJECT
public:
    ImageSelector(QTextEdit *editor, QObject *parent = nullptr);
    void setSceneManager(ImageSceneManager *manager);
    QUrl selectImage(const QPoint &pos);
    bool isImageSelected() const;

private:
    QTextEdit *editor;
    ImageSceneManager *sceneManager;
    QUrl selectedImageUrl;
};

#endif // IMAGESELECTOR_H
