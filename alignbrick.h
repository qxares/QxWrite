#ifndef ALIGNBRICK_H
#define ALIGNBRICK_H

#include <QObject>
#include <QTextEdit>

class AlignBrick : public QObject {
    Q_OBJECT
public:
    explicit AlignBrick(QTextEdit *edit, QObject *parent = nullptr);
    void align(Qt::Alignment alignment);
    void setTextEdit(QTextEdit *edit);

private:
    QTextEdit *m_textEdit;
};

#endif // ALIGNBRICK_H
