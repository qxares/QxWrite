#include "docxfilebrick.h"
#include "pandocfilebrick.h"
#include <QFile>
#include <QFileInfo>
#include <QTextDocumentWriter>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>

DocxFileBrick::DocxFileBrick(QTextEdit *textEdit, QObject *parent)
    : QObject(parent), textEdit(textEdit), pandocBrick(new PandocHandlerBrick(this)) {
    qDebug() << "DocxFileBrick initialized, target edit:" << textEdit;
}

void DocxFileBrick::setTextEdit(QTextEdit *edit) {
    textEdit = edit;
    qDebug() << "DocxFileBrick: TextEdit set to:" << textEdit;
}

QString DocxFileBrick::importFile(const QString &filePath) {
    if (!textEdit) {
        qDebug() << "DocxFileBrick: No text edit set!";
        QMessageBox::warning(nullptr, "Import Error", "No active document to import into.");
        return "";
    }
    QString htmlContent = pandocBrick->convertToHtml(filePath, "docx");
    if (!htmlContent.isEmpty()) {
        textEdit->setHtml(htmlContent);
        qDebug() << "DocxFileBrick: Imported docx:" << filePath;
    }
    return htmlContent;
}

void DocxFileBrick::exportFile(const QString &filePath) {
    if (!textEdit) {
        qDebug() << "DocxFileBrick: No text edit set!";
        QMessageBox::critical(nullptr, "Export Error", "No active document to export from.");
        return;
    }

    // Write HTML to temp file
    QString tempHtml = "/tmp/qxwrite_docxfilebrick_temp.html";
    QFile htmlFile(tempHtml);
    if (!htmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "DocxFileBrick: Failed to write temp HTML:" << tempHtml;
        QMessageBox::critical(nullptr, "Export Error", "Failed to create temp HTML file.");
        return;
    }
    QTextStream out(&htmlFile);
    out << textEdit->toHtml();
    htmlFile.close();

    // Convert HTML to DOCX with Pandoc
    if (!pandocBrick->convertFromHtml(tempHtml, filePath, "docx")) {
        qDebug() << "DocxFileBrick: Pandoc conversion failed for:" << filePath;
        QMessageBox::critical(nullptr, "Export Error", "Failed to export to DOCX.");
        QFile::remove(tempHtml);
        return;
    }

    qDebug() << "DocxFileBrick: Exported docx to:" << filePath;
    QFile::remove(tempHtml);
}
