#ifndef EXPORTBRICK_H
#define EXPORTBRICK_H

#include <QObject>
#include "exportguibrick.h"
#include "filehandlerbrick.h"

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
    FileHandlerBrick *fileHandler;
};

#endif // EXPORTBRICK_H
