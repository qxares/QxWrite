#include "savehandlerbrick.h"
#include <QDebug>

SaveHandlerBrick::SaveHandlerBrick(SaveFunctionBrick *saveFunction, SaveGUIBrick *saveGui, QObject *parent)
    : QObject(parent), m_saveFunction(saveFunction), m_saveGui(saveGui) {
    qDebug() << "SaveHandlerBrick initialized";
}

void SaveHandlerBrick::save() {
    qDebug() << "SaveHandlerBrick: save triggered";
    emit saveRequested(false);  // For "Save", don't force a prompt unless no file is set
}
