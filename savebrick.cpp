#include "savebrick.h"
#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

SaveBrick::SaveBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), targetEdit(edit) {
    qDebug() << "SaveBrick initialized, target edit:" << targetEdit;
}

void SaveBrick::save() {
    qDebug() << "SaveBrick: save triggered";
    if (!targetEdit) {
        qDebug() << "No target QTextEdit provided!";
        return;
    }
    QFileDialog dialog(nullptr, tr("Save File"), QDir::homePath());
    dialog.setNameFilter(tr("Text Files (*.txt);;All Files (*)"));
    dialog.selectNameFilter(tr("Text Files (*.txt)"));
    dialog.setDefaultSuffix("txt");  // Forces .txt in dialog UI
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted) {
        qDebug() << "SaveBrick: No file selected";
        return;
    }
    QString fileName = dialog.selectedFiles().first();
    if (!fileName.endsWith(".txt", Qt::CaseInsensitive)) {
        fileName += ".txt";
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "SaveBrick: Failed to open file:" << fileName;
        return;
    }
    QTextStream out(&file);
    out << targetEdit->toHtml();
    file.close();
    qDebug() << "File saved:" << fileName;
}
