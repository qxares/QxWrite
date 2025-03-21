#ifndef SAVEBRICK_H
#define SAVEBRICK_H

#include <QObject>

class QTextEdit;

class SaveBrick : public QObject {
    Q_OBJECT
public:
    explicit SaveBrick(QTextEdit *edit, QObject *parent = nullptr);

public slots:
    void save();

signals:
    void saved(QString fileName);

private:
    QTextEdit *targetEdit;
    QString currentFile;
};

#endif // SAVEBRICK_H
