#include "savemanagerbrick.h"
#include "savehandlerbrick.h"
#include <QDebug>

SaveManagerBrick::SaveManagerBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent) {
    SaveFunctionBrick *function = new SaveFunctionBrick(edit, this);
    SaveGuiBrick *gui = new SaveGuiBrick(this);
    SaveHandlerBrick *handler = new SaveHandlerBrick(function, gui, this);
    m_saveAction = handler->saveAction();
    qDebug() << "SaveManagerBrick initialized";
}

QAction *SaveManagerBrick::saveAction() const {
    return m_saveAction;
}
