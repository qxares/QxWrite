#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <QImage>
#include <QUrl>
#include <QTextImageFormat>

class ImageHandler {
public:
    ImageHandler(const QString &filePath);
    bool isValid() const;
    QTextImageFormat getFormat() const;
    QUrl getUrl() const;
    QSize getOriginalSize() const;

private:
    QImage image;
    QUrl placeholderUrl;
    QTextImageFormat format;
};

#endif // IMAGEHANDLER_H
