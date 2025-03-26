#include "openfilebrick.h"
#include "dialogbrick.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
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
            QString content = in.readAll();
            if (!content.isEmpty()) {
                m_textEdit->setPlainText(content);
                qDebug() << "OpenFileBrick: Loaded file:" << fileName;
            } else {
                qDebug() << "OpenFileBrick: File is empty:" << fileName;
            }
            file.close();
        } else {
            qDebug() << "OpenFileBrick: Failed to open file:" << fileName
                     << "Error:" << file.errorString();
        }
    } else {
        qDebug() << "OpenFileBrick: No file selected";
    }
}
