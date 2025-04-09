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

    QString templatePath = "/home/ares/Downloads/editor/QxWriteProject/templates/template docx.ott";
    QString tempOdt = "/tmp/qxwrite_docxfilebrick_temp.odt";

    // Copy template to temp file
    if (!QFile::copy(templatePath, tempOdt)) {
        qDebug() << "DocxFileBrick: Failed to copy template to:" << tempOdt;
        QMessageBox::critical(nullptr, "Export Error", "Failed to prepare temp file.");
        return;
    }

    // Write content to temp ODT
    QTextDocumentWriter writer(tempOdt, "odf");
    if (!writer.write(textEdit->document())) {
        qDebug() << "DocxFileBrick: Failed to write to temp ODT:" << tempOdt;
        QMessageBox::critical(nullptr, "Export Error", "Failed to write content to temp file.");
        QFile::remove(tempOdt);
        return;
    }
    qDebug() << "DocxFileBrick: Temp ODT written to:" << tempOdt;

    // Convert ODT to DOCX using soffice
    QProcess process;
    QStringList args;
    args << "--headless" << "--convert-to" << "docx" << tempOdt << "--outdir" << QFileInfo(filePath).absolutePath();
    qDebug() << "DocxFileBrick: Running soffice command: soffice" << args.join(" ");
    process.start("soffice", args);

    if (!process.waitForFinished(15000) || process.exitCode() != 0) {
        qDebug() << "DocxFileBrick: soffice conversion failed:" << process.errorString()
                 << "Output:" << process.readAllStandardError();
        QFile::remove(tempOdt);
        QMessageBox::critical(nullptr, "Export Error", "Failed to convert to " + filePath);
        return;
    }

    QString tempDocx = QFileInfo(filePath).absolutePath() + "/qxwrite_docxfilebrick_temp.docx";
    if (!QFile::exists(tempDocx)) {
        qDebug() << "DocxFileBrick: DOCX file not created:" << tempDocx;
        QFile::remove(tempOdt);
        QMessageBox::critical(nullptr, "Export Error", "Conversion failed to produce " + filePath);
        return;
    }

    // Rename to final file
    if (QFile::exists(filePath)) QFile::remove(filePath);
    if (!QFile::rename(tempDocx, filePath)) {
        qDebug() << "DocxFileBrick: Failed to rename" << tempDocx << "to" << filePath;
        QFile::remove(tempOdt);
        QFile::remove(tempDocx);
        QMessageBox::critical(nullptr, "Export Error", "Failed to finalize " + filePath);
        return;
    }

    qDebug() << "DocxFileBrick: Exported docx to:" << filePath;
    QFile::remove(tempOdt);
}
