#ifndef IMAGEPOSITIONER_H
#define IMAGEPOSITIONER_H

#include <QTextEdit>
#include <QUrl>
#include <QRect>

class ImagePositioner {
public:
    ImagePositioner(QTextEdit *editor);
    QRect getImageRect(const QUrl &imageUrl, const QPoint &pos);

private:
    QTextEdit *editor;
};

#endif // IMAGEPOSITIONER_H
