#include "openfilebrick.h"
#include <QFileDialog>
#include <QTextEdit>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QTextDocument>
#include <QMessageBox>
#include <QDebug>

OpenFileBrick::OpenFileBrick(QTextEdit *edit, QObject *parent) 
    : QObject(parent), m_textEdit(edit) {
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
    QWidget *parentWidget = qobject_cast<QWidget*>(parent());
    if (!parentWidget) {
        qDebug() << "OpenFileBrick: No parent widget for dialog, using null parent";
        parentWidget = nullptr;
    }
    qDebug() << "OpenFileBrick: openFile triggered, parent:" << parentWidget;

    QFileDialog dialog(parentWidget, "Open File", "/home/ares",
                       "Text Files (*.txt);;Rich Text Files (*.rtf);;HTML Files (*.html *.htm);;All Files (*)");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);

    dialog.selectFile("");
    if (dialog.exec() != QDialog::Accepted || dialog.selectedFiles().isEmpty()) {
        qDebug() << "OpenFileBrick: No file selected or dialog canceled";
        return;
    }

    QString fileName = dialog.selectedFiles().first();
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "OpenFileBrick: Failed to open file:" << fileName
                 << "Error:" << file.errorString();
        QMessageBox::critical(parentWidget, "Open File",
                              QString("Failed to open file: %1\nError: %2")
                              .arg(fileName).arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString content = in.readAll();
    file.close();

    if (content.isEmpty()) {
        qDebug() << "OpenFileBrick: File is empty:" << fileName;
        QMessageBox::warning(parentWidget, "Open File", "The selected file is empty.");
        return;
    }

    QString ext = QFileInfo(fileName).suffix().toLower();
    if (ext == "txt") {
        m_textEdit->setPlainText(content);
        qDebug() << "OpenFileBrick: Loaded .txt file:" << fileName;
    } else if (ext == "rtf" || ext == "html" || ext == "htm") {
        m_textEdit->setHtml(content);
        qDebug() << "OpenFileBrick: Loaded" << ext << "file as HTML:" << fileName;
    } else {
        m_textEdit->setPlainText(content);
        qDebug() << "OpenFileBrick: Loaded unknown file as plain text:" << fileName;
    }

    m_textEdit->document()->setModified(false); // Reset modified flag after load
}
