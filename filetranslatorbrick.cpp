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
    }
    return content;
}

void FileTranslatorBrick::exportFile(const QString &filePath, const QString &format) {
    if (!textEdit) {
        qDebug() << "FileTranslatorBrick: No text edit set!";
        return;
    }

    if (format == "txt") {
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "FileTranslatorBrick: Failed to write txt:" << filePath;
            QMessageBox::critical(nullptr, "Export Error", "Failed to write " + filePath);
            return;
        }
        QTextStream txtOut(&file);
        txtOut.setCodec("UTF-8");
        txtOut << textEdit->toPlainText();
        file.close();
        qDebug() << "FileTranslatorBrick: Exported txt to:" << filePath;
    }
}
