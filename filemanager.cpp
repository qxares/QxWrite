#include "filemanager.h"
#include <QDebug>

FileManager::FileManager(QObject *parent) : QObject(parent), currentEditor(nullptr) {}

DocumentWindow *FileManager::createEditor(ImageSceneManager *sceneManager) {
    qDebug() << "FileManager creating editor...";
    currentEditor = new DocumentWindow(sceneManager);
    emit editorCreated(currentEditor);
    return currentEditor;
}

void FileManager::newFile() { createEditor(nullptr); }  // Temporary, will refine later
void FileManager::openFile() { qDebug() << "Open file not implemented yet"; }
void FileManager::saveFile() { qDebug() << "Save file not implemented yet"; }

