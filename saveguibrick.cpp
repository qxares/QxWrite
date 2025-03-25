#include "saveguibrick.h"
#include "dialogbrick.h"
#include <QTextEdit>
#include <QDebug>

SaveGUIBrick::SaveGUIBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    m_dialog = new DialogBrick(this);
    qDebug() << "SaveGUIBrick initialized";
}

void SaveGUIBrick::save(bool saveAs) {
    qDebug() << "SaveGUIBrick: save triggered, saveAs:" << saveAs;
    QString filePath = m_dialog->getSaveFileName(qobject_cast<QWidget*>(parent()), "Save As", "", "Text Files (*.txt);;Markdown Files (*.md);;All Files (*)");
    if (!filePath.isEmpty()) {
        qDebug() << "SaveGUIBrick: File selected for save:" << filePath;
        emit saveRequested(filePath);
    } else {
        qDebug() << "SaveGUIBrick: Save cancelled";
    }
}
