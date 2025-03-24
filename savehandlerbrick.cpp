#include "savehandlerbrick.h"
#include <QDebug>

SaveHandlerBrick::SaveHandlerBrick(QTextEdit *textEdit, SaveFunctionBrick *function, DialogBrick *dialog, QObject *parent)
    : QObject(parent), m_textEdit(textEdit), m_saveFunction(function), m_dialog(dialog) {}

void SaveHandlerBrick::handleSave() {
    qDebug() << "SaveHandlerBrick: save triggered";
    QString fileName = m_dialog->getSaveFileName("Save File", "", "Markdown (*.md);;Text (*.txt)");
    if (!fileName.isEmpty()) {
        m_saveFunction->saveFile(fileName, m_textEdit);
    }
}
