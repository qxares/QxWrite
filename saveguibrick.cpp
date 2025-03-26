#include "saveguibrick.h"
#include "dialogbrick.h"
#include <QTextEdit>
#include <QWidget>
#include <QDebug>

SaveGUIBrick::SaveGUIBrick(QTextEdit *edit, QObject *parent) 
    : QObject(parent), m_textEdit(edit) {
    m_dialog = new DialogBrick(this);
    qDebug() << "SaveGUIBrick initialized";
}

void SaveGUIBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    qDebug() << "SaveGUIBrick: TextEdit updated to:" << m_textEdit;
}

QString SaveGUIBrick::getSaveFileName() {
    if (!m_textEdit) {
        qDebug() << "SaveGUIBrick: No text edit set, returning empty filename";
        return QString();
    }
    QWidget *parentWidget = m_textEdit->parentWidget();
    QString fileName = m_dialog->getSaveFileName(
        parentWidget,
        "Save File",
        "/home/ares",
        "Text Files (*.txt);;All Files (*)"
    );
    qDebug() << "SaveGUIBrick: Got file name:" << fileName;
    return fileName;
}
