#include "openfilebrick.h"
#include "dialogbrick.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QTextDocument>
#include <QMessageBox>
#include <QDebug>

OpenFileBrick::OpenFileBrick(QTextEdit *edit, QObject *parent) 
    : QObject(parent), m_textEdit(edit) {
    m_dialog = new DialogBrick(this);
    qDebug() << "OpenFileBrick initialized, target edit:" << m_textEdit;
}

void OpenFileBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    qDebug() << "OpenFileBrick: TextEdit updated to:" << m_textEdit;
}

void OpenFileBrick::openFile() {
    if (!m_textEdit) {
        qDebug() << "OpenFileBrick: No text edit set, cannot open file";
        return;
    }
    QWidget *parentWidget = m_textEdit->parentWidget();
    qDebug() << "OpenFileBrick: openFile triggered, parent:" << parentWidget;

    QString fileName = m_dialog->getOpenFileName(
        parentWidget,
        "Open File",
        "/home/ares",
        "Text Files (*.txt *.md);;All Files (*)"
    );

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            in.setCodec("UTF-8"); // Ensure UTF-8 encoding
            QString content = in.readAll();
            file.close();

            if (!content.isEmpty()) {
                // Try loading as HTML first (for rich text support)
                QTextDocument doc;
                doc.setHtml(content);
                QString plainText = doc.toPlainText();
                if (!plainText.isEmpty() && plainText != content) {
                    m_textEdit->setHtml(content);
                    qDebug() << "OpenFileBrick: Loaded file as HTML:" << fileName;
                } else {
                    // Fall back to plain text
                    m_textEdit->setPlainText(content);
                    qDebug() << "OpenFileBrick: Loaded file as plain text:" << fileName;
                }
            } else {
                qDebug() << "OpenFileBrick: File is empty:" << fileName;
                QMessageBox::warning(parentWidget, "Open File", "The selected file is empty.");
            }
        } else {
            qDebug() << "OpenFileBrick: Failed to open file:" << fileName
                     << "Error:" << file.errorString();
            QMessageBox::critical(parentWidget, "Open File", 
                                  QString("Failed to open file: %1\nError: %2")
                                  .arg(fileName).arg(file.errorString()));
        }
    } else {
        qDebug() << "OpenFileBrick: No file selected";
    }
}
