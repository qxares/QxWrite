// exportbrick.cpp
#include "exportbrick.h"
#include "dialogbrick.h"
#include <QFileDialog>
#include <QFile>
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
    QString filter = "All Files (*)";
    QString baseFileName = dialog.getSaveFileName(nullptr, "Export File", "/home/ares/test", filter);
    if (baseFileName.isEmpty()) {
        qDebug() << "ExportBrick: No file selected or dialog cancelled";
        return;
    }

    baseFileName.replace(" ", "_");
    if (baseFileName.contains(".")) {
        baseFileName = baseFileName.left(baseFileName.lastIndexOf("."));
    }
    qDebug() << "ExportBrick: Base filename:" << baseFileName;

    QString tempHtml = "/tmp/qxwrite_temp_export.html";
    QFile htmlFile(tempHtml);
    if (!htmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "ExportBrick: Failed to write temp HTML:" << tempHtml;
        QMessageBox::critical(qobject_cast<QWidget*>(parent()), "Export Error", 
                              "Failed to prepare temp file for export.");
        return;
    }
    QTextStream out(&htmlFile);
    out.setCodec("UTF-8");
    out << "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></head><body>" 
        << m_textEdit->toHtml() << "</body></html>";
    htmlFile.close();
    qDebug() << "ExportBrick: Temp HTML written to:" << tempHtml;

    QString outputDir = QFileInfo(baseFileName).absolutePath();
    QStringList formats = {"txt", "html", "doc", "docx", "odt", "pdf"};
    bool atLeastOneSuccess = false;

    // Pre-cleanup
    QStringList existingFiles = QDir(outputDir).entryList(QStringList() << "test0001.*" << "qxwrite_temp_export.*", QDir::Files);
    for (const QString &file : existingFiles) {
        QFile::remove(outputDir + "/" + file);
        qDebug() << "ExportBrick: Pre-removed:" << outputDir + "/" + file;
    }

    for (const QString &ext : formats) {
        QString fileName = baseFileName + "." + ext;
        qDebug() << "ExportBrick: Attempting export to:" << fileName;

        if (ext == "txt") {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out.setCodec("UTF-8");
                out << m_textEdit->toPlainText();
                file.close();
                if (QFile::exists(fileName)) {
                    qDebug() << "ExportBrick: Exported as text:" << fileName;
                    atLeastOneSuccess = true;
                } else {
                    qDebug() << "ExportBrick: File not found after write:" << fileName;
                }
            } else {
                qDebug() << "ExportBrick: Failed to write text file:" << fileName;
            }
        } else if (ext == "html") {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out.setCodec("UTF-8");
                out << "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></head><body>" 
                    << m_textEdit->toHtml() << "</body></html>";
                file.close();
                if (QFile::exists(fileName)) {
                    qDebug() << "ExportBrick: Exported as HTML:" << fileName;
                    atLeastOneSuccess = true;
                } else {
                    qDebug() << "ExportBrick: File not found after write:" << fileName;
                }
            } else {
                qDebug() << "ExportBrick: Failed to write HTML file:" << fileName;
            }
        } else if (ext == "doc" || ext == "docx" || ext == "odt") {
            QProcess process;
            QString tempOutput = outputDir + "/qxwrite_temp_export." + ext;
            QStringList args = {"--headless", "--convert-to", ext, tempHtml, "--outdir", outputDir};
            process.start("libreoffice", args);
            if (process.waitForFinished(30000) && process.exitCode() == 0) {
                qDebug() << "ExportBrick: Temp output exists:" << QFile::exists(tempOutput);
                if (QFile::exists(tempOutput)) {
                    QFile::remove(fileName); // Force remove if exists
                    if (QFile::rename(tempOutput, fileName)) {
                        qDebug() << "ExportBrick: LibreOffice exported and renamed to:" << fileName;
                        atLeastOneSuccess = true;
                    } else {
                        qDebug() << "ExportBrick: Failed to rename" << tempOutput << "to" << fileName;
                    }
                } else {
                    qDebug() << "ExportBrick: LibreOffice ran but temp file not found:" << tempOutput;
                }
            } else {
                QString errorMsg = process.error() == QProcess::FailedToStart ? 
                                   "LibreOffice not found" : process.readAllStandardError();
                qDebug() << "ExportBrick: LibreOffice failed for:" << fileName << "Error:" << errorMsg;
            }
        } else if (ext == "pdf") {
            QProcess process;
            QProcess check;
            check.start("wkhtmltopdf", QStringList() << "--version");
            bool hasWkhtmltopdf = check.waitForFinished(5000) && check.exitCode() == 0;
            if (hasWkhtmltopdf) {
                process.start("wkhtmltopdf", QStringList() << "--encoding" << "UTF-8" << tempHtml << fileName);
                if (process.waitForFinished(15000) && process.exitCode() == 0) {
                    if (QFile::exists(fileName)) {
                        qDebug() << "ExportBrick: wkhtmltopdf exported:" << fileName;
                        atLeastOneSuccess = true;
                    } else {
                        qDebug() << "ExportBrick: wkhtmltopdf ran but file not found:" << fileName;
                    }
                } else {
                    QString errorMsg = process.error() == QProcess::FailedToStart ? 
                                       "wkhtmltopdf not found" : process.readAllStandardError();
                    qDebug() << "ExportBrick: wkhtmltopdf failed for:" << fileName << "Error:" << errorMsg;
                }
            } else {
                qDebug() << "ExportBrick: Skipping PDF export - wkhtmltopdf not installed";
            }
        }
    }

    QFile::remove(tempHtml);
    qDebug() << "ExportBrick: Temp HTML removed:" << tempHtml;
    QStringList strayFiles = QDir(outputDir).entryList(QStringList() << "qxwrite_temp_export.*", QDir::Files);
    for (const QString &stray : strayFiles) {
        QFile::remove(outputDir + "/" + stray);
        qDebug() << "ExportBrick: Removed stray file:" << outputDir + "/" + stray;
    }

    if (atLeastOneSuccess) {
        m_textEdit->document()->setModified(false);
        qDebug() << "ExportBrick: Export completed successfully for at least one format";
    } else {
        qDebug() << "ExportBrick: Export failed for all formats";
        QMessageBox::critical(qobject_cast<QWidget*>(parent()), "Export Error", 
                              "Failed to export any files to: " + baseFileName);
    }
}
