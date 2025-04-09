#ifndef IMPORTBRICK_H
#define IMPORTBRICK_H

#include <QObject>
#include <QTextEdit>
#include "htmlfilebrick.h"
#include "docxfilebrick.h"
#include "odtfilebrick.h"

class ImportBrick : public QObject {
    Q_OBJECT
public:
    ImportBrick(QTextEdit *textEdit, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *edit);

public slots:
    void importFile();

private:
    QTextEdit *textEdit;
    HtmlFileBrick *htmlBrick;
    DocxFileBrick *docxBrick;
    OdtFileBrick *odtBrick;
};

#endif // IMPORTBRICK_H
