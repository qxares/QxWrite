#ifndef INSERTBRICK_H
#define INSERTBRICK_H

#include <QObject>
#include <QUrl>  // For the inserted signal

class QTextEdit;

class InsertBrick : public QObject {
    Q_OBJECT
public:
    explicit InsertBrick(QTextEdit *edit, QObject *parent = nullptr);

public slots:
    void insertImage();

signals:
    void inserted(QUrl url);

private:
    QTextEdit *targetEdit;
};

#endif // INSERTBRICK_H
