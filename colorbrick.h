#ifndef COLORBRICK_H
#define COLORBRICK_H

#include <QObject>
#include <QTextEdit>

class ColorBrick : public QObject {
    Q_OBJECT
public:
    explicit ColorBrick(QTextEdit *edit, QObject *parent = nullptr);
    void changeColor();
    void setTextEdit(QTextEdit *edit);

private:
    QTextEdit *m_textEdit;
};

#endif // COLORBRICK_H
