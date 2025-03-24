#ifndef NEWFILEBRICK_H
#define NEWFILEBRICK_H

#include <QObject>

class QTextEdit;

class NewFileBrick : public QObject {
    Q_OBJECT
public:
    explicit NewFileBrick(QTextEdit *edit, QObject *parent = nullptr);

public slots:
    void newFile();

signals:
    void newFileCreated();

private:
    QTextEdit *targetEdit;
};

#endif // NEWFILEBRICK_H
