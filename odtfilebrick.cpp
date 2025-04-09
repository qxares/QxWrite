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

    QString templatePath = "/home/ares/Downloads/editor/QxWriteProject/templates/template odt.ott";
    QString tempOdt = filePath;

    // Copy template to target file
    if (!QFile::copy(templatePath, tempOdt)) {
        qDebug() << "OdtFileBrick: Failed to copy template to:" << tempOdt;
        QMessageBox::critical(nullptr, "Export Error", "Failed to prepare target file.");
        return;
    }

    // Write content to ODT
    QTextDocumentWriter writer(tempOdt, "odf");
    if (!writer.write(textEdit->document())) {
        qDebug() << "OdtFileBrick: Failed to write to ODT:" << tempOdt;
        QMessageBox::critical(nullptr, "Export Error", "Failed to write content to " + filePath);
        QFile::remove(tempOdt);
        return;
    }

    qDebug() << "OdtFileBrick: Exported odt to:" << filePath;
}
