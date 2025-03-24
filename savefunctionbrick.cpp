#include "savefunctionbrick.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

SaveFunctionBrick::SaveFunctionBrick() {}

bool SaveFunctionBrick::saveFile(const QString &fileName, QTextEdit *textEdit) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "SaveFunctionBrick: Failed to open file:" << fileName;
        return false;
    }
    QTextStream out(&file);
    out << textEdit->toHtml();
    file.close();
    qDebug() << "SaveFunctionBrick: File saved:" << fileName;
    return true;
}
