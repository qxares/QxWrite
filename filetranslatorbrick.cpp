#include "filetranslatorbrick.h"
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QDir>

FileTranslatorBrick::FileTranslatorBrick(QTextEdit *textEdit, QObject *parent) 
    : QObject(parent), textEdit(textEdit), formatComboBox(new QComboBox()) {
    qDebug() << "FileTranslatorBrick initialized, target edit:" << textEdit;
    populateFormats();
}

FileTranslatorBrick::~FileTranslatorBrick() {
    delete formatComboBox;
    qDebug() << "FileTranslatorBrick destroyed";
}

void FileTranslatorBrick::setTextEdit(QTextEdit *edit) {
    textEdit = edit;
    qDebug() << "FileTranslatorBrick: TextEdit set to:" << textEdit;
}

void FileTranslatorBrick::populateFormats() {
    formatComboBox->clear();
    formatComboBox->addItem("Plain Text (.txt)", "txt");
    formatComboBox->addItem("HTML (.html)", "html");
    formatComboBox->addItem("Word Document (.docx)", "docx");
    formatComboBox->addItem("OpenDocument (.odt)", "odt");
    formatComboBox->addItem("PDF (.pdf)", "pdf");
    formatComboBox->setCurrentText("Plain Text (.txt)");
    qDebug() << "FileTranslatorBrick: Populated" << formatComboBox->count() << "formats";
}

QComboBox* FileTranslatorBrick::getFormatComboBox() const {
    return formatComboBox;
}

QString FileTranslatorBrick::importFile(const QString &filePath) {
    if (!textEdit) {
        qDebug() << "FileTranslatorBrick: No text edit set!";
        return "";
    }

    QFileInfo fileInfo(filePath);
    QString ext = fileInfo.suffix().toLower();
    QString content;

    if (ext == "txt") {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "FileTranslatorBrick: Failed to open txt:" << filePath;
            QMessageBox::warning(nullptr, "Import Failed", "Couldn’t open " + filePath);
            return "";
        }
        QTextStream in(&file);
        content = in.readAll();
        file.close();
        textEdit->setPlainText(content);
        qDebug() << "FileTranslatorBrick: Imported txt:" << filePath;
    } else if (ext == "pdf") {
        QProcess process;
        QString tempTxt = "/tmp/qxwrite_filetranslator_temp.txt";
        process.start("pdftotext", {filePath, tempTxt});
        if (!process.waitForFinished(15000) || process.exitCode() != 0) {
            qDebug() << "FileTranslatorBrick: pdftotext failed:" << process.errorString()
                     << "Output:" << process.readAllStandardError();
            QMessageBox::warning(nullptr, "Import Failed", "Couldn’t extract text from " + filePath);
            QFile::remove(tempTxt);
            return "";
        }
        QFile file(tempTxt);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "FileTranslatorBrick: Failed to read temp txt:" << tempTxt;
            QMessageBox::warning(nullptr, "Import Failed", "Couldn’t read extracted text.");
            QFile::remove(tempTxt);
            return "";
        }
        QTextStream in(&file);
        content = in.readAll();
        file.close();
        QFile::remove(tempTxt);
        textEdit->setPlainText(content);
        qDebug() << "FileTranslatorBrick: Imported pdf via pdftotext:" << filePath;
    } else {
        content = convertToHtml(filePath, ext);
        if (!content.isEmpty()) {
            textEdit->setHtml(content);
            qDebug() << "FileTranslatorBrick: Imported via pandoc:" << filePath;
        }
    }
    return content;
}

void FileTranslatorBrick::exportFile(const QString &filePath, const QString &format) {
    if (!textEdit) {
        qDebug() << "FileTranslatorBrick: No text edit set!";
        return;
    }

    QString tempHtml = "/tmp/qxwrite_filetranslator_temp.html";
    QFile htmlFile(tempHtml);
    if (!htmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "FileTranslatorBrick: Failed to write temp HTML:" << tempHtml;
        QMessageBox::critical(nullptr, "Export Error", "Failed to prepare temp file.");
        return;
    }
    QTextStream out(&htmlFile);
    out.setCodec("UTF-8");
    out << "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"></head><body>" 
        << textEdit->toHtml() << "</body></html>";
    htmlFile.close();
    qDebug() << "FileTranslatorBrick: Temp HTML written to:" << tempHtml;

    qDebug() << "FileTranslatorBrick: Exporting to:" << filePath;

    if (format == "txt") {
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "FileTranslatorBrick: Failed to write txt:" << filePath;
            QMessageBox::critical(nullptr, "Export Error", "Failed to write " + filePath);
            QFile::remove(tempHtml);
            return;
        }
        QTextStream txtOut(&file);
        txtOut.setCodec("UTF-8");
        txtOut << textEdit->toPlainText();
        file.close();
        qDebug() << "FileTranslatorBrick: Exported txt to:" << filePath;
    } else {
        if (convertFromHtml(tempHtml, filePath, format)) {
            qDebug() << "FileTranslatorBrick: Exported via pandoc to:" << filePath;
        }
    }
    QFile::remove(tempHtml);
}

QString FileTranslatorBrick::convertToHtml(const QString &inputFile, const QString &inputFormat) {
    QString tempHtml = "/tmp/qxwrite_filetranslator_import.html";
    QProcess process;
    QStringList args = {"-s", "--metadata", "pagetitle=ImportedDoc", "-f", inputFormat, "-t", "html", "--standalone", inputFile, "-o", tempHtml};
    process.start("pandoc", args);

    if (!process.waitForFinished(15000) || process.exitCode() != 0) {
        qDebug() << "FileTranslatorBrick: Pandoc import failed:" << process.errorString()
                 << "Output:" << process.readAllStandardError();
        QMessageBox::warning(nullptr, "Import Failed", "Pandoc conversion failed for " + inputFile);
        QFile::remove(tempHtml);
        return "";
    }

    QFile file(tempHtml);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "FileTranslatorBrick: Failed to read temp HTML:" << tempHtml;
        QMessageBox::warning(nullptr, "Import Failed", "Couldn’t read converted file.");
        QFile::remove(tempHtml);
        return "";
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    QFile::remove(tempHtml);
    qDebug() << "FileTranslatorBrick: Converted to HTML:" << inputFile;
    return content;
}

bool FileTranslatorBrick::convertFromHtml(const QString &htmlFile, const QString &outputFile, const QString &outputFormat) {
    QProcess process;
    // Ensure the output file path is absolute
    QFileInfo fileInfo(outputFile);
    QString absoluteOutputFile = fileInfo.absoluteFilePath();
    qDebug() << "FileTranslatorBrick: Current working directory:" << QDir::currentPath();
    qDebug() << "FileTranslatorBrick: Converting HTML to" << absoluteOutputFile << "format:" << outputFormat;
    QStringList args = {"-s", "-f", "html", "-t", outputFormat, "--standalone", htmlFile, "-o", absoluteOutputFile};
    process.start("pandoc", args);

    if (!process.waitForFinished(15000) || process.exitCode() != 0) {
        qDebug() << "FileTranslatorBrick: Pandoc export failed:" << process.errorString()
                 << "Output:" << process.readAllStandardError();
        QMessageBox::critical(nullptr, "Export Error", "Pandoc conversion failed for " + outputFile);
        QFile::remove(absoluteOutputFile);
        return false;
    }

    if (!QFile::exists(absoluteOutputFile)) {
        qDebug() << "FileTranslatorBrick: Output file not created:" << absoluteOutputFile;
        QMessageBox::critical(nullptr, "Export Error", "Conversion ran but no file was created.");
        return false;
    }
    return true;
}
