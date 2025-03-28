#ifndef TABLEBRICK_H
#define TABLEBRICK_H

#include <QObject>
#include <QTextEdit>

class TableBrick : public QObject {
    Q_OBJECT
public:
    explicit TableBrick(QTextEdit *textEdit, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *textEdit);
    void insertTable();

private:
    QTextEdit *m_textEdit;
};

#endif // TABLEBRICK_H
