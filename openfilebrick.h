#ifndef OPENFILEBRICK_H
#define OPENFILEBRICK_H

#include <QObject>
class QTextEdit;
class DialogBrick;

class OpenFileBrick : public QObject {
    Q_OBJECT
public:
    OpenFileBrick(QTextEdit *edit, DialogBrick *dialog, QObject *parent = nullptr);

public slots:  // Add this
    void openFile();

private:
    QTextEdit *targetEdit;
    DialogBrick *dialogBrick;
};

#endif // OPENFILEBRICK_H
