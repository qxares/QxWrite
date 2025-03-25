#ifndef INSERTBRICK_H
#define INSERTBRICK_H

#include <QObject>
#include <QTextEdit>

class DialogBrick;

class InsertBrick : public QObject {
    Q_OBJECT
public:
    InsertBrick(QTextEdit *edit, QObject *parent = nullptr);
    void insertImage();

private:
    QTextEdit *targetEdit;
    DialogBrick *dialogBrick;
};

#endif // INSERTBRICK_H
