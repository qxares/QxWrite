// importbrick.cpp
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
    QString filter = "Text (*.txt);;HTML (*.html);;Word (*.doc);;Word XML (*.docx);;OpenDocument (*.odt);;PDF (*.pdf);;All Files (*)";
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
            return;
        }
        QTextStream in(&file);
        content = in.readAll();
        file.close();
        textEdit->setHtml(content);
        qDebug() << "ImportBrick: Imported HTML file:" << fileName;
    } else if (ext == "doc" || ext == "docx" || ext == "odt" || ext == "pdf") {
        QString tempHtml = QFileInfo(fileName).baseName() + ".html";
        QString tempPath = "/tmp/" + tempHtml;
        QProcess process;
        QStringList args = {"--headless", "--convert-to", "html", fileName, "--outdir", "/tmp"};
        process.start("libreoffice", args);
        if (process.waitForFinished(15000) && process.exitCode() == 0) {
            QFile htmlFile(tempPath);
            if (htmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&htmlFile);
                content = in.readAll();
                qDebug() << "ImportBrick: Temp HTML content (first 500 chars):" << content.left(500);
                htmlFile.close();
                QFile::remove(tempPath);
                textEdit->setHtml(content);
                qDebug() << "ImportBrick: Converted and imported:" << fileName;
            } else {
                qDebug() << "ImportBrick: Failed to read temp HTML:" << tempPath;
                return;
            }
        } else {
            qDebug() << "ImportBrick: Conversion failed for:" << fileName
                     << "Error:" << process.errorString() << "Output:" << process.readAllStandardError();
            return;
        }
    } else {
        qDebug() << "ImportBrick: Unsupported file format:" << ext;
        return;
    }
}
