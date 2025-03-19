#ifndef QXWRITE_H
#define QXWRITE_H

#include <QMainWindow>
#include "imagescenemanager.h"
#include "documentwindow.h"

class QMdiArea;
class MenuManager;
class FileManager;
class ImagePlaceholderInserter;
class ImageManipulator;
class ImageResizer;
class ImageSelector;
class QAction;

class QxWrite : public QMainWindow {
    Q_OBJECT
public:
    explicit QxWrite(QWidget *parent = nullptr);
    ~QxWrite();

private slots:
    void handleNewFile();
    void handleOpenFile();
    void handleSaveFile();
    void handleEditorCreated(DocumentWindow *editor);
    void insertImageToActiveEditor();

private:
    QMdiArea *mdiArea;
    ImageSceneManager *sceneManager;
    MenuManager *menuManager;
    FileManager *fileManager;
    ImagePlaceholderInserter *inserter;
    ImageManipulator *manipulator;
    ImageResizer *resizer;
    ImageSelector *selector;
    QAction *moveAction;
    QAction *resizeAction;
};

#endif // QXWRITE_H
