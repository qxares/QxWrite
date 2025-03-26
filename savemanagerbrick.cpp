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
    if (!m_textEdit) {
        qDebug() << "SaveManagerBrick: No text edit set, cannot save";
        return;
    }
    QString fileName = m_gui->getSaveFileName();
    if (!fileName.isEmpty()) {
        m_function->save(fileName);
        qDebug() << "SaveManagerBrick: Save triggered for file:" << fileName;
    } else {
        qDebug() << "SaveManagerBrick: Save cancelled or no filename provided";
    }
}

void SaveManagerBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    m_gui->setTextEdit(edit);  // Ensure GUI brick updates too
    qDebug() << "SaveManagerBrick: TextEdit updated to:" << m_textEdit;
}
