#include "insertbrick.h"
#include <QFileDialog>
#include <QTextCursor>
#include <QTextImageFormat>
#include <QTextDocument>
#include <QTextEdit>
#include <QDebug>

InsertBrick::InsertBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), targetEdit(edit) {
    qDebug() << "InsertBrick initialized, target edit:" << targetEdit;
}

void InsertBrick::insertImage() {
    qDebug() << "InsertBrick: insertImage triggered";
    if (!targetEdit) {
        qDebug() << "No target QTextEdit provided!";
        return;
    }
    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Select Image"), "/home/ares/Pictures", tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug() << "Selected file:" << fileName;
    if (!fileName.isEmpty()) {
        QTextDocument *doc = targetEdit->document();
        QUrl url = QUrl::fromLocalFile(fileName);
        doc->addResource(QTextDocument::ImageResource, url, QPixmap(fileName));
        QTextCursor cursor = targetEdit->textCursor();
        QTextImageFormat format;
        format.setName(url.toString());
        cursor.insertImage(format);
        qDebug() << "Image inserted:" << fileName;
        emit inserted(url);
    }
}
