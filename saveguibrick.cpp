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

QString SaveGUIBrick::getSaveFileName() {
    QWidget *parentWidget = m_textEdit->parentWidget();
    QString fileName = m_dialog->getSaveFileName(
        parentWidget,
        "Save File",
        "",
        "Text Files (*.txt);;All Files (*)"
    );
    qDebug() << "SaveGUIBrick: Got file name:" << fileName;
    return fileName;
}
