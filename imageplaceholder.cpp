#include "imageplaceholder.h"
#include <QRandomGenerator>
#include <QDebug>

int ImagePlaceholder::counter = 0;

ImagePlaceholder::ImagePlaceholder(const QString &filePath) {
    image = QImage(filePath);
    if (isValid()) {
        placeholderUrl = QUrl(QString("placeholder://img_%1").arg(counter++));
        format.setName(placeholderUrl.toString());
        format.setWidth(100);
        format.setHeight(117);
    }
}

bool ImagePlaceholder::isValid() const {
    return !image.isNull();
}

QTextImageFormat ImagePlaceholder::getFormat() const {
    return format;
}

QUrl ImagePlaceholder::getUrl() const {
    return placeholderUrl;
}

QImage ImagePlaceholder::getImage() const {
    return image;
}
