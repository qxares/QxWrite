#include "wysiwygimagehandler.h"
#include <QTextCursor>
#include <QTextImageFormat>
#include <QDebug>

WYSIWYGImageHandler::WYSIWYGImageHandler(QTextEdit *editor) : editor(editor), rubberBand(nullptr), cursorPos(-1) {}

WYSIWYGImageHandler::~WYSIWYGImageHandler() {
    delete rubberBand;
}

void WYSIWYGImageHandler::startScaling(const QUrl &imageUrl, const QPoint &startPos) {
    this->imageUrl = imageUrl;
    this->startPos = startPos;
    QTextCursor cursor = editor->cursorForPosition(startPos);
    QTextImageFormat format = cursor.charFormat().toImageFormat();
    if (format.isValid() && format.name() == imageUrl.toString()) {
        startSize = QSize(format.width(), format.height());
        cursorPos = cursor.position();
        imageRect = editor->cursorRect(cursor);
        imageRect.setSize(startSize);  // Match image size
        rubberBand = new QRubberBand(QRubberBand::Rectangle, editor);
        rubberBand->setGeometry(imageRect);
        rubberBand->show();
        editor->setCursor(Qt::SizeFDiagCursor);
        qDebug() << "Starting scaling for" << imageUrl << "Start size:" << startSize << "at" << imageRect;
    }
}

void WYSIWYGImageHandler::updateScaling(const QPoint &currentPos) {
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
        qDebug() << "Scaling to" << newWidth << "x" << newHeight;
    }
}

void WYSIWYGImageHandler::finishScaling() {
    if (!imageUrl.isEmpty()) {
        delete rubberBand;
        rubberBand = nullptr;
        imageUrl.clear();
        cursorPos = -1;
        editor->unsetCursor();
        qDebug() << "Scaling finished";
    }
}
