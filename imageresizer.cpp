#include "imageresizer.h"
#include <QTextCursor>
#include <QTextImageFormat>
#include <QDebug>

ImageResizer::ImageResizer(QTextEdit *editor) : editor(editor), rubberBand(nullptr), cursorPos(-1) {}

ImageResizer::~ImageResizer() {
    delete rubberBand;
}

void ImageResizer::startResizing(const QUrl &imageUrl, const QPoint &startPos, const QRect &imageRect) {
    this->imageUrl = imageUrl;
    this->startPos = startPos;
    this->imageRect = imageRect;
    QTextCursor cursor = editor->cursorForPosition(startPos);
    QTextImageFormat format = cursor.charFormat().toImageFormat();
    if (format.isValid() && format.name() == imageUrl.toString()) {
        startSize = QSize(format.width(), format.height());
        cursorPos = cursor.position();
        rubberBand = new QRubberBand(QRubberBand::Rectangle, editor);
        rubberBand->setGeometry(imageRect);
        rubberBand->show();
        editor->setCursor(Qt::SizeFDiagCursor);
        qDebug() << "Starting resizing for" << imageUrl << "Start size:" << startSize << "at" << imageRect;
    }
}

void ImageResizer::updateResizing(const QPoint ¤tPos) {
    if (imageUrl.isEmpty() || !rubberBand || cursorPos == -1) return;
    int deltaX = currentPos.x() - startPos.x();
    int newWidth = qMax(50, startSize.width() + deltaX);
    qreal aspectRatio = static_cast<qreal>(startSize.height()) / startSize.width();
    int newHeight = qMax(50, static_cast<int>(newWidth * aspectRatio));
    int maxWidth = editor->viewport()->width() - imageRect.left();
    newWidth = qMin(newWidth, maxWidth);
    newHeight = qMin(newHeight, static_cast<int>(maxWidth * aspectRatio));

    QRect newRect = imageRect;
    newRect.setSize(QSize(newWidth, newHeight));
    rubberBand->setGeometry(newRect);

    QTextCursor cursor(editor->document());
    cursor.setPosition(cursorPos);
    if (cursor.charFormat().isImageFormat()) {
        QTextImageFormat format = cursor.charFormat().toImageFormat();
        format.setWidth(newWidth);
        format.setHeight(newHeight);
        cursor.setCharFormat(format);
        editor->viewport()->update();
        qDebug() << "Resizing to" << newWidth << "x" << newHeight;
    }
}

void ImageResizer::finishResizing() {
    if (!imageUrl.isEmpty()) {
        delete rubberBand;
        rubberBand = nullptr;
        imageUrl.clear();
        cursorPos = -1;
        editor->unsetCursor();
        qDebug() << "Resizing finished";
    }
}
