#include "exportbrick.h"
#include "dialogbrick.h"
#include <QTextEdit>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>

ExportBrick::ExportBrick(QTextEdit *edit, QObject *parent) 
    : QObject(parent), m_textEdit(edit) {
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
    DialogBrick dialog(this);
    QString fileName = dialog.getSaveFileName(nullptr, "Export File", "/home/ares", 
                                              "Word (*.doc);;Word XML (*.docx);;OpenDocument (*.odt);;PDF (*.pdf);;All Files (*)");
    if (fileName.isEmpty()) {
        qDebug() << "ExportBrick: No file selected";
        return;
    }

    QString ext = QFileInfo(fileName).suffix().toLower();
    if (ext.isEmpty()) {
        fileName += ".docx";  // Default to DOCX
        ext = "docx";
    }

    // Save as temp HTML first
    QString tempHtml = "/tmp/qxwrite_temp_export.html";
    QFile htmlFile(tempHtml);
    if (htmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&htmlFile);
        out.setCodec("UTF-8");
        out << m_textEdit->toHtml();
        htmlFile.close();
        qDebug() << "ExportBrick: Temp HTML written to:" << tempHtml;
    } else {
        qDebug() << "ExportBrick: Failed to write temp HTML:" << tempHtml;
        QMessageBox::critical(qobject_cast<QWidget*>(parent()), "Export Error", 
                              "Failed to prepare file for export.");
        return;
    }

    QProcess process;
    bool success = false;
    QString errorMsg;
    if (ext == "doc" || ext == "docx" || ext == "odt") {
        QStringList args = QStringList() << "--headless" << "--convert-to" << ext << tempHtml 
                         << "--outdir" << QFileInfo(fileName).absolutePath();
        process.start("libreoffice", args);
        success = process.waitForFinished(10000);
        if (success && process.exitCode() == 0) {
            qDebug() << "ExportBrick: LibreOffice conversion successful for:" << fileName;
        } else {
            errorMsg = process.error() == QProcess::FailedToStart ? 
                       "LibreOffice not found or failed to start" : process.readAllStandardError();
            success = false;
        }
    } else if (ext == "pdf") {
        process.start("pandoc", QStringList() << tempHtml << "-o" << fileName);
        success = process.waitForFinished(10000);
        if (success && process.exitCode() == 0) {
            qDebug() << "ExportBrick: Pandoc conversion successful for:" << fileName;
        } else {
            errorMsg = process.error() == QProcess::FailedToStart ? 
                       "Pandoc not found or failed to start" : process.readAllStandardError();
            success = false;
        }
    }

    if (success) {
        qDebug() << "ExportBrick: Exported as" << ext << ":" << fileName;
        QFile::remove(tempHtml);  // Clean up
        m_textEdit->document()->setModified(false);
    } else {
        qDebug() << "ExportBrick: Export failed for:" << fileName << "Error:" << errorMsg;
        QMessageBox::critical(qobject_cast<QWidget*>(parent()), "Export Error", 
                              "Failed to export file: " + fileName + "\nError: " + errorMsg);
    }
}
