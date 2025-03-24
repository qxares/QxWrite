#include "saveguibrick.h"
#include "dialogbrick.h"
#include <QDebug>

SaveGUIBrick::SaveGUIBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), m_edit(edit), m_currentFilePath("") {
    m_dialog = new DialogBrick(this);
    qDebug() << "SaveGUIBrick initialized";
}

void SaveGUIBrick::save(bool forcePrompt) {
    if (forcePrompt || m_currentFilePath.isEmpty()) {
        QString filePath = m_dialog->getSaveFileName("Save As", "", "Text Files (*.txt);;Markdown Files (*.md);;All Files (*)");
        if (!filePath.isEmpty()) {
            m_currentFilePath = filePath;
            emit fileSelected(m_currentFilePath);
        } else {
            qDebug() << "SaveGUIBrick: Save cancelled";
        }
    } else {
        emit fileSelected(m_currentFilePath);
    }
}
