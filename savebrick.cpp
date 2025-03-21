#include "savebrick.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTextEdit>
#include <QDebug>

SaveBrick::SaveBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), targetEdit(edit), currentFile("") {
    qDebug() << "SaveBrick initialized, target edit:" << targetEdit;
}

void SaveBrick::save() {
    qDebug() << "SaveBrick: save triggered";
    if (!targetEdit) {
        qDebug() << "No target QTextEdit provided!";
        return;
    }
    QString fileName = currentFile.isEmpty() ?
        QFileDialog::getSaveFileName(nullptr, tr("Save File"), "", tr("Text Files (*.txt)")) :
        currentFile;
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << targetEdit->toPlainText();
            file.close();
            currentFile = fileName;
            qDebug() << "File saved:" << fileName;
            emit saved(fileName);
        } else {
            qDebug() << "Failed to save file:" << fileName;
        }
    }
}
