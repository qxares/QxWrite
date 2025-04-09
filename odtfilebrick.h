#ifndef ODTFILEBRICK_H
#define ODTFILEBRICK_H

#include <QObject>
#include <QTextEdit>
#include "pandocfilebrick.h"

class OdtFileBrick : public QObject {
    Q_OBJECT
public:
    explicit OdtFileBrick(QTextEdit *textEdit, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *edit);
    QString importFile(const QString &filePath);
    void exportFile(const QString &filePath);

private:
    QTextEdit *textEdit;
    PandocHandlerBrick *pandocBrick;
};

#endif // ODTFILEBRICK_H
