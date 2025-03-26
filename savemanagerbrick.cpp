#include "savemanagerbrick.h"
#include "savefunctionbrick.h"
#include "saveguibrick.h"
#include "savehandlerbrick.h"
#include <QDebug>

SaveManagerBrick::SaveManagerBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    m_function = new SaveFunctionBrick(this);
    m_gui = new SaveGUIBrick(this);
    m_handler = new SaveHandlerBrick(this);
    qDebug() << "SaveManagerBrick initialized with textEdit:" << m_textEdit;
}

void SaveManagerBrick::triggerSave() {
    if (m_textEdit) m_handler->save(m_textEdit->toPlainText(), m_gui->saveFile());
}

void SaveManagerBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    qDebug() << "SaveManagerBrick: TextEdit updated to:" << m_textEdit;
}
