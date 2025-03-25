#ifndef ALIGNBRICK_H
#define ALIGNBRICK_H

#include <QObject>
#include <QTextEdit>

class AlignBrick : public QObject {
    Q_OBJECT
public:
    enum Alignment { AlignLeft, AlignCenter, AlignRight };
    AlignBrick(QTextEdit *edit, Alignment align, QObject *parent = nullptr);
    void align();

private:
    QTextEdit *textEdit;
    Alignment alignment;
};

#endif // ALIGNBRICK_H
