#include "openfilebrick.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QDir>  // Added this
#include <QDebug>
#include "dialogbrick.h"

OpenFileBrick::OpenFileBrick(QTextEdit *edit, DialogBrick *dialog, QObject *parent)
    : QObject(parent), targetEdit(edit), dialogBrick(dialog) {
    qDebug() << "OpenFileBrick initialized, target edit:" << targetEdit;
}

void OpenFileBrick::openFile() {
    qDebug() << "OpenFileBrick: openFile triggered";
    if (!targetEdit) {
        qDebug() << "No target QTextEdit provided!";
        return;
    }
    QString fileName = dialogBrick->getOpenFileName(tr("Open File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) {
        qDebug() << "OpenFileBrick: No file selected";
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "OpenFileBrick: Failed to open file:" << fileName;
        return;
    }
    QTextStream in(&file);
    targetEdit->setHtml(in.readAll());
    file.close();
    qDebug() << "File opened:" << fileName;
}
