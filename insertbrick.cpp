#include "insertbrick.h"
#include <QFileDialog>
#include <QTextCursor>
#include <QTextImageFormat>
#include <QTextDocument>
#include <QDebug>

InsertBrick::InsertBrick(QObject *parent)
    : QObject(parent), targetEdit(nullptr) {
    if (auto *window = qobject_cast<QMainWindow*>(parent)) {
        targetEdit = window->findChild<QTextEdit*>();
    }
    qDebug() << "InsertBrick initialized, target edit:" << targetEdit;
}

void InsertBrick::insertImage() {
    qDebug() << "InsertBrick: insertImage triggered";
    if (!targetEdit) {
        qDebug() << "No target QTextEdit found!";
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
