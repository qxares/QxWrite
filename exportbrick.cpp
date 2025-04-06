#include "exportbrick.h"
#include <QTextEdit>
#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QDir>

ExportBrick::ExportBrick(QTextEdit *edit, QObject *parent) 
    : QObject(parent), 
      m_textEdit(edit), 
      guiBrick(new ExportGUIBrick(this)), 
      fileHandler(new FileHandlerBrick(this)) {
    qDebug() << "ExportBrick initialized, target edit:" << m_textEdit;
}

void ExportBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    qDebug() << "ExportBrick: TextEdit updated to:" << m_textEdit;
}

void ExportBrick::exportFile() {
    if (!m_textEdit) {
        qDebug() << "ExportBrick: No text edit set, cannot export";
        return;
    }

    QString fileName;
    QString format;
    if (!guiBrick->getExportDetails(fileName, format)) {
        qDebug() << "ExportBrick: No file selected or dialog cancelled";
        return;
    }

    // Ensure the fileName includes the full path
    QFileInfo fileInfo(fileName);
    QString absoluteFilePath = fileInfo.absoluteFilePath();
    if (!fileName.startsWith("/home/ares/test/")) {
        absoluteFilePath = "/home/ares/test/" + fileInfo.fileName();
    }
    qDebug() << "ExportBrick: Exporting to absolute path:" << absoluteFilePath << "with format:" << format;

    // Set wait cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);
    bool success = fileHandler->handleExport(absoluteFilePath, format, m_textEdit);
    // Restore cursor
    QApplication::restoreOverrideCursor();

    if (success && QFile::exists(absoluteFilePath)) {
        m_textEdit->document()->setModified(false);
        qDebug() << "ExportBrick: Successfully exported to:" << absoluteFilePath;
    } else {
        qDebug() << "ExportBrick: Export failed, file not found at:" << absoluteFilePath;
    }
}
