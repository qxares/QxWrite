#ifndef TABLEHANDLERBRICK_H
#define TABLEHANDLERBRICK_H

#include <QObject>
#include <QTextEdit>
#include <Qt>

class TableHandlerBrick : public QObject {
    Q_OBJECT
public:
    explicit TableHandlerBrick(QTextEdit *textEdit, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *textEdit);

public slots:
    void alignTableLeft();
    void alignTableCenter();
    void alignTableRight();
    void deleteTable();

private:
    QTextTable* findTableInDocument(); // Renamed and improved
    void alignTable(Qt::Alignment alignment);
    QTextEdit *m_textEdit;
};

#endif // TABLEHANDLERBRICK_H
