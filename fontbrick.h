#ifndef FONTBRICK_H
#define FONTBRICK_H

#include <QObject>
#include <QTextEdit>

class FontBrick : public QObject {
    Q_OBJECT
public:
    explicit FontBrick(QTextEdit *edit, QObject *parent = nullptr);
    void changeFont();
    void setTextEdit(QTextEdit *edit);

private:
    QTextEdit *m_textEdit;
};

#endif // FONTBRICK_H
