#include "openfilebrick.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include "dialogbrick.h"

OpenFileBrick::OpenFileBrick(QTextEdit *edit, DialogBrick *dialog, QObject *parent)
    : QObject(parent), targetEdit(edit), dialogBrick(dialog) {
    qDebug() << "OpenFileBrick initialized, target edit:" << targetEdit << ", dialog:" << dialogBrick;
}

void OpenFileBrick::openFile() {
    qDebug() << "OpenFileBrick: openFile triggered, targetEdit:" << targetEdit << ", dialogBrick:" << dialogBrick;
    
    // Check targetEdit
    if (!targetEdit) {
        qDebug() << "OpenFileBrick: Error - No target QTextEdit provided!";
        QMessageBox::critical(nullptr, "Error", "No target QTextEdit provided!");
        return;
    }
    
    // Check dialogBrick
    if (!dialogBrick) {
        qDebug() << "OpenFileBrick: Error - DialogBrick is null!";
        QMessageBox::critical(nullptr, "Error", "DialogBrick is not initialized!");
        return;
    }
    
    // Get file name with explicit parent and filters
    QWidget *parentWidget = targetEdit->window();
    qDebug() << "OpenFileBrick: Parent widget for dialog:" << parentWidget;
    QString fileName = dialogBrick->getOpenFileName(tr("Open File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*)"));
    
    qDebug() << "OpenFileBrick: File selected:" << fileName;
    if (fileName.isEmpty()) {
        qDebug() << "OpenFileBrick: No file selected or dialog cancelled";
        return;
    }
    
    // Open and read file
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "OpenFileBrick: Failed to open file:" << fileName << "Error:" << file.errorString();
        QMessageBox::critical(parentWidget, "Error", "Failed to open file: " + file.errorString());
        return;
    }
    
    QTextStream in(&file);
    QString content = in.readAll();
    targetEdit->setHtml(content);
    file.close();
    
    qDebug() << "OpenFileBrick: File opened and loaded:" << fileName;
}
