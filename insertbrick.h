#ifndef INSERTBRICK_H
#define INSERTBRICK_H

#include <QObject>

class QTextEdit;
class DialogBrick;

class InsertBrick : public QObject {
    Q_OBJECT
public:
    InsertBrick(QTextEdit *edit, DialogBrick *dialog, QObject *parent = nullptr);
    ~InsertBrick() override = default;

public slots:
    void insertImage();

private:
    QTextEdit *targetEdit;
    DialogBrick *dialogBrick;
};

#endif // INSERTBRICK_H
