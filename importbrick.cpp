#include "importbrick.h"
#include "dialogbrick.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QScopedPointer>

ImportBrick::ImportBrick(QTextEdit *textEdit, QObject *parent) : QObject(parent), textEdit(textEdit) {
    qDebug() << "ImportBrick initialized, target edit:" << textEdit;
}

void ImportBrick::setTextEdit(QTextEdit *edit) {
    textEdit = edit;
    qDebug() << "ImportBrick: TextEdit set to:" << textEdit;
}

void ImportBrick::importFile() {
    if (!textEdit) {
        qDebug() << "ImportBrick: No text edit set!";
        return;
    }

    DialogBrick dialog(this);
    QString filter = "Text (*.txt);;HTML (*.html);;Word (*.doc *.docx);;OpenDocument (*.odt);;PDF (*.pdf);;All Files (*)";
    QString fileName = dialog.getOpenFileName(nullptr, "Import File", "/home/ares/test", filter);
    if (fileName.isEmpty()) {
        qDebug() << "ImportBrick: No file selected";
        return;
    }

    QString ext = QFileInfo(fileName).suffix().toLower();
    QString content;

    qDebug() << "ImportBrick: Importing file:" << fileName << "with extension:" << ext;

    if (ext == "txt") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "ImportBrick: Failed to open file:" << fileName;
            QMessageBox::warning(nullptr, "Import Failed", "Couldn’t open " + fileName + ". Check permissions or file type.");
            return;
        }
        QTextStream in(&file);
        content = in.readAll();
        file.close();
        textEdit->setPlainText(content);
        qDebug() << "ImportBrick: Imported plain text file:" << fileName;
    } else if (ext == "html") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "ImportBrick: Failed to open file:" << fileName;
            QMessageBox::warning(nullptr, "Import Failed", "Couldn’t open " + fileName + ". Check permissions or file type.");
            return;
        }
        QTextStream in(&file);
        content = in.readAll();
        file.close();
        textEdit->setHtml(content);
        qDebug() << "ImportBrick: Imported HTML file:" << fileName;
    } else if (ext == "doc" || ext == "docx" || ext == "odt" || ext == "pdf") {
        QProcess checkProcess;
        checkProcess.start("libreoffice", {"--version"});
        bool libreOfficeInstalled = checkProcess.waitForFinished(5000) && checkProcess.exitCode() == 0;
        
        if (!libreOfficeInstalled) {
            qDebug() << "ImportBrick: LibreOffice not found for:" << fileName;
            QMessageBox::warning(nullptr, "Import Error", 
                "LibreOffice is required for " + ext.toUpper() + " files but isn’t installed.\n"
                "Try importing as plain text or HTML instead.");
            return;
        }

        QString tempHtml = QFileInfo(fileName).baseName() + ".html";
        QString tempPath = "/tmp/" + tempHtml;
        QProcess process;
        QStringList args = {"--headless", "--convert-to", "html", fileName, "--outdir", "/tmp"};
        process.start("libreoffice", args);
        
        if (process.waitForFinished(15000) && process.exitCode() == 0) {
            QScopedPointer<QFile> htmlFile(new QFile(tempPath));
            if (htmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(htmlFile.data());
                content = in.readAll();
                qDebug() << "ImportBrick: Temp HTML content (first 500 chars):" << content.left(500);
                textEdit->setHtml(content);
                qDebug() << "ImportBrick: Converted and imported:" << fileName;
            } else {
                qDebug() << "ImportBrick: Failed to read temp HTML:" << tempPath;
                QMessageBox::warning(nullptr, "Import Failed", "Conversion succeeded, but couldn’t read the temp file.");
            }
            // QScopedPointer ensures cleanup even on failure
        } else {
            QFile::remove(tempPath); // Manual cleanup if process fails
            qDebug() << "ImportBrick: Conversion failed for:" << fileName
                     << "Error:" << process.errorString() << "Output:" << process.readAllStandardError();
            QMessageBox::warning(nullptr, "Import Failed", 
                "Failed to convert " + fileName + ".\nError: " + process.errorString());
        }
    } else {
        qDebug() << "ImportBrick: Unsupported file format:" << ext;
        QMessageBox::warning(nullptr, "Unsupported Format", 
            "The file type ‘." + ext + "’ isn’t supported yet.\nTry .txt, .html, .doc, .docx, .odt, or .pdf.");
    }
}
