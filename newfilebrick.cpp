#include "newfilebrick.h"
#include <QTextEdit>
#include <QDebug>

NewFileBrick::NewFileBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), targetEdit(edit) {
    qDebug() << "NewFileBrick initialized, target edit:" << targetEdit;
}

void NewFileBrick::newFile() {
    qDebug() << "NewFileBrick: newFile triggered";
    if (!targetEdit) {
        qDebug() << "No target QTextEdit provided!";
        return;
    }
    targetEdit->clear();
    emit newFileCreated();
}
