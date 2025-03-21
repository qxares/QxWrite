#include "openfilebrick.h"
#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

OpenFileBrick::OpenFileBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), targetEdit(edit) {
    qDebug() << "OpenFileBrick initialized, target edit:" << targetEdit;
}

void OpenFileBrick::openFile() {
    qDebug() << "OpenFileBrick: openFile triggered";
    if (!targetEdit) {
        qDebug() << "No target QTextEdit provided!";
        return;
    }
    QString filter = tr("Text Files (*.txt);;All Files (*)");
    QString selectedFilter = tr("Text Files (*.txt)");
    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open File"), QDir::homePath(), filter, &selectedFilter);
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
