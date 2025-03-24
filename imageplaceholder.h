#ifndef IMAGEPLACEHOLDER_H
#define IMAGEPLACEHOLDER_H

#include <QImage>
#include <QUrl>
#include <QTextImageFormat>

class ImagePlaceholder {
public:
    ImagePlaceholder(const QString &filePath);
    bool isValid() const;
    QTextImageFormat getFormat() const;
    QUrl getUrl() const;
    QImage getImage() const;

private:
    QImage image;
    QUrl placeholderUrl;
    QTextImageFormat format;
    static int counter;  // Unique ID for placeholders
};

#endif // IMAGEPLACEHOLDER_H
