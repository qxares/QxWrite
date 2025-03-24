#include "insertbrick.h"
#include <QTextEdit>
#include <QTextCursor>
#include <QTextImageFormat>
#include <QDebug>
#include "dialogbrick.h"

InsertBrick::InsertBrick(QTextEdit *edit, DialogBrick *dialog, QObject *parent)
    : QObject(parent), targetEdit(edit), dialogBrick(dialog) {
    qDebug() << "InsertBrick initialized, target edit:" << edit;
}

void InsertBrick::insertImage() {
    QString fileName = dialogBrick->getOpenFileName(
        "Insert Image", "", "Images (*.png *.jpg *.jpeg *.gif *.bmp)");
    if (!fileName.isEmpty()) {
        QTextCursor cursor = targetEdit->textCursor();
        QTextImageFormat format;
        format.setName(fileName);
        cursor.insertImage(format);
        qDebug() << "InsertBrick: Image inserted:" << fileName;
    } else {
        qDebug() << "InsertBrick: No image selected";
    }
}
