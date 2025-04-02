#include "savefunctionbrick.h"
#include <QTextEdit>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QTextDocument>
#include <QMessageBox>
#include <QDebug>

SaveFunctionBrick::SaveFunctionBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    qDebug() << "SaveFunctionBrick initialized";
}

void SaveFunctionBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    qDebug() << "SaveFunctionBrick: TextEdit updated to:" << m_textEdit;
}

void SaveFunctionBrick::save(const QString &fileName) {
    if (!m_textEdit) {
        qDebug() << "SaveFunctionBrick: No text edit set, cannot save";
        return;
    }
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        QString ext = QFileInfo(fileName).suffix().toLower();
        if (ext == "txt") {
            out << m_textEdit->toPlainText();
            qDebug() << "SaveFunctionBrick: Saved as .txt:" << fileName;
        } else if (ext == "rtf" || ext == "html" || ext == "htm") {
            out << m_textEdit->toHtml();
            qDebug() << "SaveFunctionBrick: Saved as" << ext << ":" << fileName;
        } else {
            out << m_textEdit->toPlainText();
            qDebug() << "SaveFunctionBrick: Saved unknown type as plain text:" << fileName;
        }
        file.close();
        m_textEdit->document()->setModified(false); // Clear modified flag
    } else {
        qDebug() << "SaveFunctionBrick: Failed to save file:" << fileName
                 << "Error:" << file.errorString();
        QMessageBox::critical(m_textEdit->parentWidget(), "Save File",
                              QString("Failed to save file: %1\nError: %2")
                              .arg(fileName).arg(file.errorString()));
    }
}
