#include "imagepositioner.h"
#include <QTextCursor>
#include <QTextImageFormat>
#include <QDebug>

ImagePositioner::ImagePositioner(QTextEdit *editor) : editor(editor) {}

QRect ImagePositioner::getImageRect(const QUrl &imageUrl, const QPoint &pos) {
    QTextCursor cursor = editor->cursorForPosition(pos);
    QTextImageFormat format = cursor.charFormat().toImageFormat();
    if (format.isValid() && format.name() == imageUrl.toString()) {
        QRect rect = editor->cursorRect(cursor);
        rect.setSize(QSize(format.width(), format.height()));
        qDebug() << "Positioned image at" << rect;
        return rect;
    }
    qDebug() << "No valid image position for" << imageUrl << "at" << pos;
    return QRect();
}
