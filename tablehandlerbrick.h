#ifndef TABLEHANDLERBRICK_H
#define TABLEHANDLERBRICK_H

#include <QObject>
#include <QTextEdit>

class TableHandlerBrick : public QObject {
    Q_OBJECT
public:
    explicit TableHandlerBrick(QTextEdit *textEdit, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *textEdit);

public slots:
    void deleteTable();

private:
    QTextTable* findTableInDocument();
    QTextEdit *m_textEdit;
};

#endif // TABLEHANDLERBRICK_H
