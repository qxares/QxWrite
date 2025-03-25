#include "newfilebrick.h"
#include <QTextEdit>
#include <QDebug>

NewFileBrick::NewFileBrick(QTextEdit *edit, QObject *parent) 
    : QObject(parent), targetEdit(edit) {
    qDebug() << "NewFileBrick initialized, target edit:" << targetEdit;
}

void NewFileBrick::newFile() {
    qDebug() << "NewFileBrick: Creating new document";
    targetEdit->clear();
    targetEdit->setDocumentTitle("Untitled");
}
