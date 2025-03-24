#include "savefunctionbrick.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>  // Added this
#include <QDebug>

SaveFunctionBrick::SaveFunctionBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), m_edit(edit) {
}

void SaveFunctionBrick::save(const QString &filePath) {
    if (!m_edit) {
        qDebug() << "SaveFunctionBrick: No target QTextEdit provided!";
        QMessageBox::critical(nullptr, "Error", "No target QTextEdit provided!");
        return;
    }
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << m_edit->toHtml();
        file.close();
        qDebug() << "SaveFunctionBrick: File saved:" << filePath;
    } else {
        qDebug() << "SaveFunctionBrick: Failed to save file:" << filePath << "Error:" << file.errorString();
        QMessageBox::critical(m_edit->window(), "Error", "Failed to save file: " + file.errorString());
    }
}
