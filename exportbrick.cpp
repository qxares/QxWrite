#include "exportbrick.h"
#include <QTextEdit>
#include <QDebug>
#include <QFile>
#include <QApplication>

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

    qDebug() << "ExportBrick: Exporting to:" << fileName << "with format:" << format;

    // Set wait cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);
    bool success = fileHandler->handleExport(fileName, format, m_textEdit);
    // Restore cursor
    QApplication::restoreOverrideCursor();

    if (success && QFile::exists(fileName)) {
        m_textEdit->document()->setModified(false);
        qDebug() << "ExportBrick: Successfully exported to:" << fileName;
    } else {
        qDebug() << "ExportBrick: Export failed, file not found at:" << fileName;
    }
}
