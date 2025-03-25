#ifndef NEWFILEBRICK_H
#define NEWFILEBRICK_H

#include <QObject>
#include <QTextEdit>

class NewFileBrick : public QObject {
    Q_OBJECT
public:
    NewFileBrick(QTextEdit *edit, QObject *parent = nullptr);
    void newFile();

private:
    QTextEdit *targetEdit;
};

#endif // NEWFILEBRICK_H
