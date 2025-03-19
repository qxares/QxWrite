#ifndef IMAGERESIZER_H
#define IMAGERESIZER_H

#include <QTextEdit>
#include <QUrl>
#include <QPoint>
#include <QRubberBand>

class ImageResizer {
public:
    ImageResizer(QTextEdit *editor);
    ~ImageResizer();
    void startResizing(const QUrl &imageUrl, const QPoint &startPos, const QRect &imageRect);
    void updateResizing(const QPoint ¤tPos);
    void finishResizing();

private:
    QTextEdit *editor;
    QUrl imageUrl;
    QPoint startPos;
    QSize startSize;
    QRect imageRect;
    QRubberBand *rubberBand;
    int cursorPos;
};

#endif // IMAGERESIZER_H
