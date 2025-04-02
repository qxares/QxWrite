#ifndef EXPORTBRICK_H
#define EXPORTBRICK_H

#include <QObject>
#include <QString>

class QTextEdit;

class ExportBrick : public QObject {
    Q_OBJECT
public:
    explicit ExportBrick(QTextEdit *edit, QObject *parent = nullptr);
    void exportFile();
    void setTextEdit(QTextEdit *edit);

private:
    QTextEdit *m_textEdit;
};

#endif // EXPORTBRICK_H
