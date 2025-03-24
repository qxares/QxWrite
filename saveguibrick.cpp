#include "saveguibrick.h"
#include <QFileDialog>
#include <QDebug>

SaveGUIBrick::SaveGUIBrick(QObject *parent) : QObject(parent) {
}

QString SaveGUIBrick::getSaveFileName() {
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Markdown Files (*.md);;All Files (*)");
    if (!fileName.isEmpty()) {
        qDebug() << "SaveGUIBrick: Save selected:" << fileName;
    }
    return fileName;
}
