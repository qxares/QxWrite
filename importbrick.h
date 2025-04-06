#ifndef IMPORTBRICK_H
#define IMPORTBRICK_H

#include <QObject>
#include <QTextEdit>
#include "filetranslatorbrick.h"

class ImportBrick : public QObject {
    Q_OBJECT
public:
    ImportBrick(QTextEdit *textEdit, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *edit);  // Add setter

public slots:
    void importFile();

private:
    QTextEdit *textEdit;
    FileTranslatorBrick *fileTranslator;  // Added for file format conversion
};

#endif // IMPORTBRICK_H
