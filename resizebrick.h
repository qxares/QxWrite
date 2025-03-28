#ifndef RESIZEBRICK_H
#define RESIZEBRICK_H

#include <QObject>
#include <QTextEdit>

class ResizeBrick : public QObject {
    Q_OBJECT
public:
    explicit ResizeBrick(QTextEdit *textEdit, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *textEdit);
    void enableResize(); // Hook into QTextEdit events
    void moveObject();   // Right-click move like cascade
    bool eventFilter(QObject *obj, QEvent *event) override; // Add eventFilter declaration

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    QTextEdit *m_textEdit;
    bool m_resizing;
    QPoint m_startPos;
    QTextTable *m_currentTable;
    QTextImageFormat m_currentImage;
};

#endif // RESIZEBRICK_H
