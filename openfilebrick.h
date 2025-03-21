#ifndef OPENFILEBRICK_H
#define OPENFILEBRICK_H

#include <QObject>

class QTextEdit;

class OpenFileBrick : public QObject {
    Q_OBJECT
public:
    explicit OpenFileBrick(QTextEdit *edit, QObject *parent = nullptr);

public slots:
    void openFile();

private:
    QTextEdit *targetEdit;
};

#endif // OPENFILEBRICK_H
