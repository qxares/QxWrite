#include "savehandlerbrick.h"
#include "savefunctionbrick.h"
#include "saveguibrick.h"
#include <QDebug>

SaveHandlerBrick::SaveHandlerBrick(SaveFunctionBrick *saveFunction, SaveGuiBrick *saveGui, QObject *parent)
    : QObject(parent), m_saveFunction(saveFunction), m_saveGui(saveGui) {
    m_saveAction = new QAction("Save", this);
    connect(m_saveAction, &QAction::triggered, this, &SaveHandlerBrick::handleSave);
}

void SaveHandlerBrick::handleSave() {
    qDebug() << "SaveHandlerBrick: save triggered";
    QString fileName = m_saveGui->getSaveFileName();
    if (!fileName.isEmpty()) {
        m_saveFunction->save(fileName);
    }
}

QAction *SaveHandlerBrick::saveAction() const {
    return m_saveAction;
}
