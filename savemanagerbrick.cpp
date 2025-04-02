#include "savemanagerbrick.h"
#include "savefunctionbrick.h"
#include "saveguibrick.h"
#include "savehandlerbrick.h"
#include <QTextEdit>
#include <QDebug>

SaveManagerBrick::SaveManagerBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    m_function = new SaveFunctionBrick(m_textEdit, this);
    m_gui = new SaveGUIBrick(m_textEdit, this);
    m_handler = new SaveHandlerBrick(m_function, m_gui, this);
    m_lastSavedFileName = "";
    qDebug() << "SaveManagerBrick initialized with textEdit:" << m_textEdit;
}

SaveManagerBrick::~SaveManagerBrick() {
    delete m_handler;
    delete m_gui;
    delete m_function;
    qDebug() << "SaveManagerBrick destroyed";
}

void SaveManagerBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    m_gui->setTextEdit(edit);
    m_function->setTextEdit(edit);
    qDebug() << "SaveManagerBrick: TextEdit updated to:" << m_textEdit;
}

bool SaveManagerBrick::triggerSave() {
    if (!m_textEdit) {
        qDebug() << "SaveManagerBrick: No text edit set, cannot save";
        return false;
    }
    QString fileName = m_lastSavedFileName;
    if (fileName.isEmpty()) {
        fileName = m_gui->getSaveFileName(true); // Prompt only if no previous save
    }
    if (!fileName.isEmpty()) {
        m_function->save(fileName);
        m_lastSavedFileName = fileName;
        qDebug() << "SaveManagerBrick: Save triggered for file:" << fileName;
        return true;
    } else {
        qDebug() << "SaveManagerBrick: Save cancelled or no filename provided";
        return false;
    }
}

void SaveManagerBrick::triggerSaveAs() {
    if (!m_textEdit || !m_textEdit->document()) {
        qDebug() << "SaveManagerBrick: No valid text edit or document, cannot save as";
        return;
    }
    QString fileName = m_gui->getSaveFileName(true); // Always prompt for Save As
    if (!fileName.isEmpty()) {
        m_function->save(fileName);
        m_lastSavedFileName = fileName;
        qDebug() << "SaveManagerBrick: Save As triggered for file:" << fileName;
    } else {
        qDebug() << "SaveManagerBrick: Save As cancelled or no filename provided";
    }
}
