#include "savemanagerbrick.h"
#include "savefunctionbrick.h"
#include "saveguibrick.h"
#include "savehandlerbrick.h"
#include <QTextEdit>
#include <QDebug>

SaveManagerBrick::SaveManagerBrick(QTextEdit *edit, QObject *parent) 
    : QObject(parent), m_textEdit(edit) {
    m_function = new SaveFunctionBrick(m_textEdit, this);
    m_gui = new SaveGUIBrick(m_textEdit, this);
    m_handler = new SaveHandlerBrick(m_function, m_gui, this);

    qDebug() << "SaveManagerBrick initialized with textEdit:" << m_textEdit;
}

void SaveManagerBrick::triggerSave() {
    qDebug() << "SaveManagerBrick: Triggering save";
    m_handler->handleSave();
}
