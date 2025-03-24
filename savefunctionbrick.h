#ifndef SAVEFUNCTIONBRICK_H
#define SAVEFUNCTIONBRICK_H

#include <QString>
#include <QTextEdit>

class SaveFunctionBrick {
public:
    SaveFunctionBrick();
    bool saveFile(const QString &fileName, QTextEdit *textEdit);
};

#endif // SAVEFUNCTIONBRICK_H
