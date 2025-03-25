#include "savehandlerbrick.h"
#include "savefunctionbrick.h"
#include "saveguibrick.h"
#include <QDebug>

SaveHandlerBrick::SaveHandlerBrick(SaveFunctionBrick *saveFunction, SaveGUIBrick *saveGui, QObject *parent) 
    : QObject(parent), m_saveFunction(saveFunction), m_saveGui(saveGui) {
    qDebug() << "SaveHandlerBrick initialized";
}

void SaveHandlerBrick::handleSave() {
    qDebug() << "SaveHandlerBrick: Handling save";
    QString fileName = m_saveGui->getSaveFileName();
    if (!fileName.isEmpty()) {
        m_saveFunction->save(fileName);
    }
}
