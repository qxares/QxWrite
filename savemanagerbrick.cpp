#include "savemanagerbrick.h"
#include "saveguibrick.h"
#include "savehandlerbrick.h"
#include "savefunctionbrick.h"
#include <QTextEdit>
#include <QDebug>

SaveManagerBrick::SaveManagerBrick(QTextEdit *edit, QObject *parent) : QObject(parent) {
    m_gui = new SaveGUIBrick(edit, this);
    m_handler = new SaveHandlerBrick(this);
    m_function = new SaveFunctionBrick(edit, this);

    qDebug() << "SaveManagerBrick initialized";

    connect(m_gui, &SaveGUIBrick::saveRequested, m_function, &SaveFunctionBrick::save);
    connect(m_handler, &SaveHandlerBrick::saveTriggered, m_gui, &SaveGUIBrick::save);
}

void SaveManagerBrick::triggerSave() {
    qDebug() << "SaveManagerBrick: Triggering save";
    m_handler->triggerSave();
}
