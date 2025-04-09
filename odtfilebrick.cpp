#include "odtfilebrick.h"
#include "pandocfilebrick.h"
#include <QFile>
#include <QTextDocumentWriter>
#include <QMessageBox>
#include <QDebug>

OdtFileBrick::OdtFileBrick(QTextEdit *textEdit, QObject *parent)
    : QObject(parent), textEdit(textEdit), pandocBrick(new PandocHandlerBrick(this)) {
    qDebug() << "OdtFileBrick initialized, target edit:" << textEdit;
}

void OdtFileBrick::setTextEdit(QTextEdit *edit) {
    textEdit = edit;
    qDebug() << "OdtFileBrick: TextEdit set to:" << textEdit;
}

QString OdtFileBrick::importFile(const QString &filePath) {
    if (!textEdit) {
        qDebug() << "OdtFileBrick: No text edit set!";
        QMessageBox::warning(nullptr, "Import Error", "No active document to import into.");
        return "";
    }
    QString htmlContent = pandocBrick->convertToHtml(filePath, "odt");
    if (!htmlContent.isEmpty()) {
        textEdit->setHtml(htmlContent);
        qDebug() << "OdtFileBrick: Imported odt:" << filePath;
    }
    return htmlContent;
}

void OdtFileBrick::exportFile(const QString &filePath) {
    if (!textEdit) {
        qDebug() << "OdtFileBrick: No text edit set!";
        QMessageBox::critical(nullptr, "Export Error", "No active document to export from.");
        return;
    }

    // Write HTML to temp file
    QString tempHtml = "/tmp/qxwrite_odtfilebrick_temp.html";
    QFile htmlFile(tempHtml);
    if (!htmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "OdtFileBrick: Failed to write temp HTML:" << tempHtml;
        QMessageBox::critical(nullptr, "Export Error", "Failed to create temp HTML file.");
        return;
    }
    QTextStream out(&htmlFile);
    out << textEdit->toHtml();
    htmlFile.close();

    // Convert HTML to ODT with Pandoc
    if (!pandocBrick->convertFromHtml(tempHtml, filePath, "odt")) {
        qDebug() << "OdtFileBrick: Pandoc conversion failed for:" << filePath;
        QMessageBox::critical(nullptr, "Export Error", "Failed to export to ODT.");
        QFile::remove(tempHtml);
        return;
    }

    qDebug() << "OdtFileBrick: Exported odt to:" << filePath;
    QFile::remove(tempHtml);
}
