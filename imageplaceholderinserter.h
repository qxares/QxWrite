#ifndef IMAGEPLACEHOLDERINSERTER_H
#define IMAGEPLACEHOLDERINSERTER_H

#include <QObject>
#include <QWidget>

class ImageSceneManager;
class DocumentWindow;

class ImagePlaceholderInserter : public QObject {
    Q_OBJECT
public:
    ImagePlaceholderInserter(ImageSceneManager *sceneManager, QWidget *parent = nullptr);
    void insertImage(DocumentWindow *docWindow); // Overload with explicit DocumentWindow

public slots:
    void insertImage(); // Keep for compatibility

private:
    ImageSceneManager *sceneManager;
};

#endif // IMAGEPLACEHOLDERINSERTER_H
