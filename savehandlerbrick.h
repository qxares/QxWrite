#ifndef SAVEHANDLERBRICK_H
#define SAVEHANDLERBRICK_H

#include <QObject>
#include "savefunctionbrick.h"
#include "saveguibrick.h"

class QTextEdit;

class SaveHandlerBrick : public QObject {
    Q_OBJECT
public:
    SaveHandlerBrick(SaveFunctionBrick *saveFunction, SaveGUIBrick *saveGui, QObject *parent = nullptr);

public slots:
    void save();  // Add this slot for "Save"

signals:
    void saveRequested(bool forcePrompt);  // Add this signal to request a file path

private:
    SaveFunctionBrick *m_saveFunction;
    SaveGUIBrick *m_saveGui;
};

#endif // SAVEHANDLERBRICK_H
