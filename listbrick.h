#ifndef LISTBRICK_H
#define LISTBRICK_H

#include <QObject>
#include <QTextEdit>

class ListBrick : public QObject {
    Q_OBJECT
public:
    explicit ListBrick(QTextEdit *textEdit, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *textEdit);
    void toggleNumbering();
    void toggleBullets();

private:
    QTextEdit *m_textEdit;
};

#endif // LISTBRICK_H
