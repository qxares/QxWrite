#include "insertbrick.h"
#include "dialogbrick.h"
#include <QTextCursor>
#include <QDebug>

InsertBrick::InsertBrick(QTextEdit *edit, QObject *parent) : QObject(parent), targetEdit(edit) {
    dialogBrick = new DialogBrick(this);
    qDebug() << "InsertBrick initialized, target edit:" << targetEdit;
}

void InsertBrick::insertImage() {
    if (targetEdit) {
        QString fileName = dialogBrick->openFileDialog("Insert Image", "Images (*.png *.jpg *.bmp)");
        if (!fileName.isEmpty()) {
            QImage image(fileName);
            if (!image.isNull()) {
                QTextCursor cursor = targetEdit->textCursor();
                cursor.insertImage(image, fileName);
            }
        }
    }
}

void InsertBrick::setTextEdit(QTextEdit *edit) {
    targetEdit = edit;
    qDebug() << "InsertBrick: TextEdit updated to:" << targetEdit;
}
