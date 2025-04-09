#ifndef LISTBRICK_H
#define LISTBRICK_H

#include <QObject>
#include <QTextEdit>

class ListBrick : public QObject {
    Q_OBJECT
public:
    explicit ListBrick(QTextEdit *edit, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *edit);

public slots:
    void toggleBullets();
    void toggleNumbering();

private:
    QTextEdit *targetEdit;
};

#endif // LISTBRICK_H
