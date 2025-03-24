#include "imageplaceholderinserter.h"
#include <QFileDialog>
#include <QTextCursor>
#include <QTextImageFormat>
#include <QDebug>
#include "imagescenemanager.h"
#include "documentwindow.h"
#include <QTextEdit>
#include <QTextDocument>

ImagePlaceholderInserter::ImagePlaceholderInserter(ImageSceneManager *sceneManager, QWidget *parent)
    : QObject(parent), sceneManager(sceneManager) {}

void ImagePlaceholderInserter::insertImage() {
    qDebug() << "Insert image (no context) triggered - should not happen!";
}

void ImagePlaceholderInserter::insertImage(DocumentWindow *docWindow) {
    qDebug() << "Insert image with DocumentWindow triggered";
    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Select Image"), "/home/ares/Pictures", tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug() << "Selected file from dialog:" << fileName;
    if (!fileName.isEmpty() && docWindow) {
        QTextEdit *textEdit = docWindow->getTextEdit();
        qDebug() << "Text edit pointer:" << textEdit;
        if (textEdit) {
            QTextDocument *doc = textEdit->document();
            QUrl url = QUrl::fromLocalFile(fileName);
            doc->addResource(QTextDocument::ImageResource, url, QPixmap(fileName));
            QTextCursor cursor = textEdit->textCursor();
            QTextImageFormat format;
            format.setName(url.toString());
            cursor.insertImage(format);
            qDebug() << "Image inserted into document:" << fileName;
        } else {
            qDebug() << "No text edit available for image insertion";
        }
    } else {
        qDebug() << "No file selected or docWindow null";
    }
}
