#ifndef OPENFILEBRICK_H
#define OPENFILEBRICK_H

#include <QObject>

class QTextEdit;
class DialogBrick;

class OpenFileBrick : public QObject {
    Q_OBJECT
public:
    explicit OpenFileBrick(QTextEdit *edit, QObject *parent = nullptr);
    void openFile();

private:
    QTextEdit *textEdit;
    DialogBrick *dialogBrick;
};

#endif // OPENFILEBRICK_H
