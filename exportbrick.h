// exportbrick.h
#ifndef EXPORTBRICK_H
#define EXPORTBRICK_H

#include <QObject>
#include <QTextEdit>

class ExportBrick : public QObject {
    Q_OBJECT
public:
    explicit ExportBrick(QTextEdit *edit, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *edit);

public slots:
    void exportFile();

private:
    QTextEdit *m_textEdit;
};

#endif // EXPORTBRICK_H
