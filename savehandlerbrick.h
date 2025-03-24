#ifndef SAVEHANDLERBRICK_H
#define SAVEHANDLERBRICK_H

#include <QObject>
#include <QAction>
#include "savefunctionbrick.h"
#include "saveguibrick.h"

class SaveHandlerBrick : public QObject {
    Q_OBJECT
public:
    SaveHandlerBrick(SaveFunctionBrick *saveFunction, SaveGuiBrick *saveGui, QObject *parent = nullptr);
    QAction *saveAction() const;

private slots:
    void handleSave();

private:
    SaveFunctionBrick *m_saveFunction;
    SaveGuiBrick *m_saveGui;
    QAction *m_saveAction;
};

#endif // SAVEHANDLERBRICK_H
