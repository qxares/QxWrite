#ifndef DOCXFILEBRICK_H
#define DOCXFILEBRICK_H

#include <QObject>
#include <QTextEdit>
#include "pandocfilebrick.h"

class DocxFileBrick : public QObject {
    Q_OBJECT
public:
    explicit DocxFileBrick(QTextEdit *textEdit, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *edit);
    QString importFile(const QString &filePath);
    void exportFile(const QString &filePath);

private:
    QTextEdit *textEdit;
    PandocHandlerBrick *pandocBrick;
};

#endif // DOCXFILEBRICK_H
