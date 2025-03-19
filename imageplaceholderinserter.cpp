#include "imageplaceholderinserter.h"
#include <QFileDialog>
#include <QTextCursor>
#include <QTextImageFormat>
#include <QDebug>
#include "imagescenemanager.h"
#include "documentwindow.h"
#include <QTextEdit>

ImagePlaceholderInserter::ImagePlaceholderInserter(ImageSceneManager *sceneManager, QWidget *parent)
    : QObject(parent), sceneManager(sceneManager) {}

void ImagePlaceholderInserter::insertImage() {
    qDebug() << "Insert image triggered";
    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Select Image"), "/home/ares/Pictures", tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug() << "Selected file from dialog:" << fileName;
    if (!fileName.isEmpty() && sceneManager) {
        QTextEdit *textEdit = qobject_cast<DocumentWindow*>(parent())->getTextEdit();
        if (textEdit) {
            QTextCursor cursor = textEdit->textCursor();
            QTextImageFormat format;
            format.setName(fileName);
            cursor.insertImage(format);
            QPixmap pixmap(fileName);
            sceneManager->addImage(QUrl::fromLocalFile(fileName), pixmap, QPoint(0, 0));
            qDebug() << "Image inserted:" << fileName;
        } else {
            qDebug() << "No text edit available for image insertion";
        }
    } else {
        qDebug() << "No file selected or sceneManager is null";
    }
}
