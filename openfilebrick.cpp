#include "openfilebrick.h"
#include "dialogbrick.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QDebug>

OpenFileBrick::OpenFileBrick(QTextEdit *edit, QObject *parent) : QObject(parent), textEdit(edit) {
    dialogBrick = new DialogBrick(this);
    qDebug() << "OpenFileBrick initialized, target edit:" << textEdit;
}

void OpenFileBrick::openFile() {
    qDebug() << "OpenFileBrick: openFile triggered, parent:" << parent();
    QWidget *parentWidget = qobject_cast<QWidget*>(parent());
    if (!parentWidget) {
        qDebug() << "OpenFileBrick: Parent widget is null, using nullptr";
        parentWidget = nullptr;
    }
    QString fileName = dialogBrick->getOpenFileName(parentWidget, "Open File", "", "Text Files (*.txt *.md);;All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            textEdit->setText(in.readAll());
            file.close();
            qDebug() << "OpenFileBrick: Loaded file:" << fileName;
        } else {
            qDebug() << "OpenFileBrick: Failed to open file:" << fileName;
        }
    } else {
        qDebug() << "OpenFileBrick: No file selected";
    }
}
