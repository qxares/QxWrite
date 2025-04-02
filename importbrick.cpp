#include "importbrick.h"
#include "dialogbrick.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QDebug>
#include <QFileInfo>

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
    QString fileName = dialog.getOpenFileName(nullptr, "Import File", "/home/ares/test", 
                                              "Text (*.txt);;HTML (*.html);;Word (*.doc);;Word XML (*.docx);;OpenDocument (*.odt);;PDF (*.pdf);;All Files (*)");
    if (fileName.isEmpty()) {
        qDebug() << "ImportBrick: No file selected";
        return;
    }

    QString ext = QFileInfo(fileName).suffix().toLower();
    QString content;

    if (ext == "txt") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "ImportBrick: Failed to open file:" << fileName;
            return;
        }
        QTextStream in(&file);
        content = in.readAll();
        file.close();
        textEdit->setPlainText(content);  // Plain text for .txt
        qDebug() << "ImportBrick: Imported plain text file:" << fileName;
    } else if (ext == "html") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "ImportBrick: Failed to open file:" << fileName;
            return;
        }
        QTextStream in(&file);
        content = in.readAll();
        file.close();
        textEdit->setHtml(content);  // HTML for .html
        qDebug() << "ImportBrick: Imported HTML file:" << fileName;
    } else if (ext == "doc" || ext == "docx" || ext == "odt" || ext == "pdf") {
        // Convert to HTML using LibreOffice
        QString tempHtml = "/tmp/qxwrite_temp_import.html";
        QProcess process;
        process.start("libreoffice", QStringList() << "--headless" << "--convert-to" << "html" 
                      << fileName << "--outdir" << "/tmp");
        if (process.waitForFinished(10000) && process.exitCode() == 0) {
            QFile htmlFile(tempHtml);
            if (htmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&htmlFile);
                content = in.readAll();
                qDebug() << "ImportBrick: Temp HTML content:" << content.left(500);  // Log first 500 chars
                htmlFile.close();
                QFile::remove(tempHtml);
                textEdit->setHtml(content);  // Load as HTML
                qDebug() << "ImportBrick: Converted and imported:" << fileName;
            } else {
                qDebug() << "ImportBrick: Failed to read temp HTML:" << tempHtml;
                return;
            }
        } else {
            qDebug() << "ImportBrick: Conversion failed for:" << fileName << process.errorString();
            return;
        }
    } else {
        qDebug() << "ImportBrick: Unsupported file format:" << ext;
        return;
    }
}
