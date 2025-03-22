#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include "documentwindow.h"  // Updated from documenteditor.h

class FileManager : public QObject {
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);
    DocumentWindow *createEditor(ImageSceneManager *sceneManager);  // Updated return type
    void newFile();
    void openFile();
    void saveFile();

signals:
    void editorCreated(DocumentWindow *editor);  // Updated signal

private:
    DocumentWindow *currentEditor;  // Updated type
};

#endif // FILEMANAGER_H
