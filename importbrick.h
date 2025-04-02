#ifndef IMPORTBRICK_H
#define IMPORTBRICK_H

#include <QObject>
#include <QTextEdit>

class ImportBrick : public QObject {
    Q_OBJECT
public:
    ImportBrick(QTextEdit *textEdit, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *edit);  // Add setter

public slots:
    void importFile();

private:
    QTextEdit *textEdit;
};

#endif // IMPORTBRICK_H
