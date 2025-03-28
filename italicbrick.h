#ifndef ITALICBRICK_H
#define ITALICBRICK_H

#include <QObject>
#include <QTextEdit>

class ItalicBrick : public QObject {
    Q_OBJECT
public:
    explicit ItalicBrick(QTextEdit *edit, QObject *parent = nullptr);
    void applyItalic();
    void setTextEdit(QTextEdit *edit);

private:
    QTextEdit *m_textEdit;
};

#endif // ITALICBRICK_H
