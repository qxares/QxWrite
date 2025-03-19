#ifndef IMAGESCALER_H
#define IMAGESCALER_H

#include <QTextEdit>
#include <QUrl>
#include <QPoint>

class ImageScaler {
public:
    ImageScaler(QTextEdit *editor);
    void startScaling(const QUrl &imageUrl, const QPoint &startPos);
    void updateScaling(const QPoint &currentPos);
    void finishScaling();

private:
    QTextEdit *editor;
    QUrl imageUrl;
    QPoint startPos;
    QSize startSize;
    QRect imageRect;
};

#endif // IMAGESCALER_H
