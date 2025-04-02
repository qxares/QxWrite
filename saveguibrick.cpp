#include "saveguibrick.h"
#include "dialogbrick.h"
#include <QTextEdit>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

SaveGUIBrick::SaveGUIBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    m_dialog = new DialogBrick(this);
    m_lastFileName = "";
    qDebug() << "SaveGUIBrick initialized";
}

void SaveGUIBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    qDebug() << "SaveGUIBrick: TextEdit updated to:" << m_textEdit;
}

QString SaveGUIBrick::getSaveFileName(bool saveAs) {
    if (!m_textEdit) {
        qDebug() << "SaveGUIBrick: No text edit set, cannot get save file name";
        return "";
    }
    if (!saveAs && !m_lastFileName.isEmpty()) {
        qDebug() << "SaveGUIBrick: Reusing last file name:" << m_lastFileName;
        return m_lastFileName;
    }

    QWidget *parentWidget = m_textEdit->parentWidget();
    QFileDialog dialog(parentWidget, saveAs ? "Save As" : "Save", "/home/ares",
                       "Text Files (*.txt);;Rich Text Files (*.rtf);;HTML Files (*.html *.htm);;All Files (*)");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);

    QString fileName;
    while (true) {
        if (dialog.exec() != QDialog::Accepted || dialog.selectedFiles().isEmpty()) {
            qDebug() << "SaveGUIBrick: Dialog cancelled, no file name set";
            return "";
        }
        fileName = dialog.selectedFiles().first();
        QString selectedFilter = dialog.selectedNameFilter();
        QString ext = QFileInfo(fileName).suffix().toLower();
        if (ext.isEmpty()) {
            if (selectedFilter.contains("*.txt")) {
                fileName += ".txt";
            } else if (selectedFilter.contains("*.rtf")) {
                fileName += ".rtf";
            } else if (selectedFilter.contains("*.html") || selectedFilter.contains("*.htm")) {
                fileName += ".html";
            }
        }
        if (QFile::exists(fileName)) {
            QMessageBox::StandardButton reply = QMessageBox::question(
                parentWidget, "File Exists",
                QString("'%1' already exists. Overwrite?").arg(fileName),
                QMessageBox::Yes | QMessageBox::No
            );
            if (reply == QMessageBox::Yes) {
                break; // Proceed with overwrite
            }
            // Loop back to dialog if No
        } else {
            break; // File doesn’t exist, proceed
        }
    }
    m_lastFileName = fileName;
    qDebug() << "SaveGUIBrick: New file name set:" << fileName;
    return fileName;
}
