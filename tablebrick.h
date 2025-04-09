#ifndef TABLEBRICK_H
#define TABLEBRICK_H

#include <QObject>
#include <QTextEdit>

class TableBrick : public QObject {
    Q_OBJECT
public:
    explicit TableBrick(QTextEdit *edit, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *edit);

public slots:
    void insertTable();
    void addRowBefore();
    void addRowAfter();
    void addColumnBefore();
    void addColumnAfter();
    void deleteRow();
    void deleteColumn();
    void deleteTable();
    void alignTableLeft();
    void alignTableCenter();
    void alignTableRight();
    void mergeCells();
    void splitCells();

private:
    QTextEdit *targetEdit;
    QTextTable* getCurrentTable();
};

#endif // TABLEBRICK_H
