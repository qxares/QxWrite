#include "imagehandler.h"
#include <QRandomGenerator>
#include <QDebug>

ImageHandler::ImageHandler(const QString &filePath) {
    image = QImage(filePath);
    if (isValid()) {
        placeholderUrl = QUrl(QString("placeholder://%1").arg(QRandomGenerator::global()->bounded(1000)));
        format.setName(placeholderUrl.toString());
        format.setWidth(100);
        format.setHeight(117);
    }
}

bool ImageHandler::isValid() const {
    return !image.isNull();
}

QTextImageFormat ImageHandler::getFormat() const {
    return format;
}

QUrl ImageHandler::getUrl() const {
    return placeholderUrl;
}

QSize ImageHandler::getOriginalSize() const {
    return image.size();
}
