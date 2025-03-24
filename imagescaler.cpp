#include "imagescaler.h"
#include <QTextCursor>
#include <QTextImageFormat>
#include <QDebug>

ImageScaler::ImageScaler(QTextEdit *editor) : editor(editor) {}

void ImageScaler::startScaling(const QUrl &imageUrl, const QPoint &startPos) {
    this->imageUrl = imageUrl;
    this->startPos = startPos;
    QTextCursor cursor = editor->cursorForPosition(startPos);
    QTextImageFormat format = cursor.charFormat().toImageFormat();
    if (format.isValid() && format.name() == imageUrl.toString()) {
        startSize = QSize(format.width(), format.height());
        imageRect = editor->cursorRect(cursor);
        editor->setCursor(Qt::SizeFDiagCursor);
        qDebug() << "Starting scaling for" << imageUrl << "Start size:" << startSize << "at" << imageRect;
    }
}

void ImageScaler::updateScaling(const QPoint ¤tPos) {
    if (imageUrl.isEmpty()) return;
    int deltaX = currentPos.x() - imageRect.right();  // From right edge
    int newWidth = qMax(50, startSize.width() + deltaX);
    qreal aspectRatio = static_cast<qreal>(startSize.height()) / startSize.width();
    int newHeight = qMax(50, static_cast<int>(newWidth * aspectRatio));
    int maxWidth = editor->viewport()->width() - imageRect.left();
    newWidth = qMin(newWidth, maxWidth);
    newHeight = qMin(newHeight, static_cast<int>(maxWidth * aspectRatio));

    QTextCursor cursor = editor->cursorForPosition(imageRect.topLeft());
    if (cursor.charFormat().isImageFormat()) {
        QTextImageFormat format = cursor.charFormat().toImageFormat();
        format.setWidth(newWidth);
        format.setHeight(newHeight);
        cursor.setCharFormat(format);
        editor->document()->markContentsDirty(cursor.position(), 1);
        qDebug() << "Scaling to" << newWidth << "x" << newHeight;
    }
}

void ImageScaler::finishScaling() {
    if (!imageUrl.isEmpty()) {
        imageUrl.clear();
        editor->unsetCursor();
        qDebug() << "Scaling finished";
    }
}
