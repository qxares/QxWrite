#ifndef EXPORTBRICK_H
#define EXPORTBRICK_H

#include <QObject>
#include "exportguibrick.h"
#include "htmlfilebrick.h"
#include "docxfilebrick.h"
#include "odtfilebrick.h"

class QTextEdit;

class ExportBrick : public QObject {
    Q_OBJECT
public:
    explicit ExportBrick(QTextEdit *edit, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *edit);
    void exportFile();

private:
    QTextEdit *m_textEdit;
    ExportGUIBrick *guiBrick;
    HtmlFileBrick *htmlBrick;
    DocxFileBrick *docxBrick;
    OdtFileBrick *odtBrick;
};

#endif // EXPORTBRICK_H
