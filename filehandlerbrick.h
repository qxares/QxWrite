#ifndef FILEHANDLERBRICK_H
#define FILEHANDLERBRICK_H

#include <QObject>
#include <QString>
#include "filetranslatorbrick.h"

class FileHandlerBrick : public QObject {
    Q_OBJECT
public:
    explicit FileHandlerBrick(QObject *parent = nullptr);
    bool handleExport(const QString &filePath, const QString &format, QTextEdit *textEdit);  // Return success/failure

private:
    FileTranslatorBrick *translator;
};

#endif // FILEHANDLERBRICK_H
