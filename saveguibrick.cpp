#include "saveguibrick.h"
#include "dialogbrick.h"  // Add this
#include <QDebug>

SaveGUIBrick::SaveGUIBrick(QObject *parent) : QObject(parent) {
}

QString SaveGUIBrick::getSaveFileName() {
    DialogBrick dialog;
    QString fileName = dialog.getSaveFileName("Save File", "", "Markdown Files (*.md);;All Files (*)");
    if (!fileName.isEmpty()) {
        qDebug() << "SaveGUIBrick: Save selected:" << fileName;
    }
    return fileName;
}
