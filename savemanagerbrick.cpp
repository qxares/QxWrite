#include "savemanagerbrick.h"
#include "savehandlerbrick.h"
#include <QDebug>

SaveManagerBrick::SaveManagerBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent) {
    SaveFunctionBrick *function = new SaveFunctionBrick(edit, this);
    m_gui = new SaveGUIBrick(this);  // Fix typo, use m_gui
    SaveHandlerBrick *handler = new SaveHandlerBrick(function, m_gui, this);
    m_saveAction = handler->saveAction();
    qDebug() << "SaveManagerBrick initialized";
}

QAction *SaveManagerBrick::saveAction() const {
    return m_saveAction;
}
