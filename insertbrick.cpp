#include "insertbrick.h"
#include "dialogbrick.h"
#include <QTextEdit>
#include <QTextCursor>
#include <QDebug>
#include <QWidget>

InsertBrick::InsertBrick(QTextEdit *edit, QObject *parent) 
    : QObject(parent), targetEdit(edit) {
    dialogBrick = new DialogBrick(this);
    qDebug() << "InsertBrick initialized, target edit:" << targetEdit;
}

void InsertBrick::insertImage() {
    QWidget *parentWidget = targetEdit->parentWidget();
    QString fileName = dialogBrick->getOpenFileName(
        parentWidget,
        "Insert Image",
        "",
        "Images (*.png *.jpg *.jpeg *.gif *.bmp)"
    );
    if (!fileName.isEmpty()) {
        QTextCursor cursor = targetEdit->textCursor();
        cursor.insertImage(fileName);
        qDebug() << "InsertBrick: Inserted image:" << fileName;
    } else {
        qDebug() << "InsertBrick: Image insertion cancelled";
    }
}
