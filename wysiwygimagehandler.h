#ifndef WYSIWYGIMAGEHANDLER_H
#define WYSIWYGIMAGEHANDLER_H

#include <QTextEdit>
#include <QUrl>
#include <QPoint>
#include <QRubberBand>

class WYSIWYGImageHandler {
public:
    WYSIWYGImageHandler(QTextEdit *editor);
    ~WYSIWYGImageHandler();
    void startScaling(const QUrl &imageUrl, const QPoint &startPos);
    void updateScaling(const QPoint &currentPos);
    void finishScaling();

private:
    QTextEdit *editor;
    QUrl imageUrl;
    QPoint startPos;
    QSize startSize;
    QRect imageRect;
    QRubberBand *rubberBand;
    int cursorPos;  // Track image’s document position
};

#endif // WYSIWYGIMAGEHANDLER_H
