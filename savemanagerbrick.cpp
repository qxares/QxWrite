#include "savemanagerbrick.h"
#include "savefunctionbrick.h"
#include "saveguibrick.h"
#include "savehandlerbrick.h"
#include <QDebug>

SaveManagerBrick::SaveManagerBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    m_function = new SaveFunctionBrick(m_textEdit, this);
    m_gui = new SaveGUIBrick(m_textEdit, this);
    m_handler = new SaveHandlerBrick(m_function, m_gui, this);
    qDebug() << "SaveManagerBrick initialized with textEdit:" << m_textEdit;
}

void SaveManagerBrick::triggerSave() {
    if (m_textEdit) {
        QString fileName = m_gui->getSaveFileName();
        if (!fileName.isEmpty()) {
            m_function->save(fileName);
        }
    }
}

void SaveManagerBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    // No dummy save—let triggerSave handle it when called
    qDebug() << "SaveManagerBrick: TextEdit updated to:" << m_textEdit;
}
