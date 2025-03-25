#include "openfilebrick.h"
#include "dialogbrick.h"
#include <QTextEdit>
#include <QDebug>

OpenFileBrick::OpenFileBrick(QTextEdit *edit, QObject *parent) : QObject(parent), textEdit(edit) {
    dialogBrick = new DialogBrick(this);
    qDebug() << "OpenFileBrick initialized, target edit:" << textEdit;
}

void OpenFileBrick::openFile() {
    qDebug() << "OpenFileBrick: openFile triggered";
    QString fileName = dialogBrick->getOpenFileName(qobject_cast<QWidget*>(parent()), "Open File", "", "Text Files (*.txt *.md);;All Files (*)");
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
