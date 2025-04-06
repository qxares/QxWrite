#include "importbrick.h"
#include "dialogbrick.h"
#include "filetranslatorbrick.h"
#include <QTextEdit>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>

ImportBrick::ImportBrick(QTextEdit *textEdit, QObject *parent) 
    : QObject(parent), textEdit(textEdit), fileTranslator(new FileTranslatorBrick(textEdit, this)) {
    qDebug() << "ImportBrick initialized, target edit:" << textEdit;
}

void ImportBrick::setTextEdit(QTextEdit *edit) {
    textEdit = edit;
    fileTranslator->setTextEdit(edit);
    qDebug() << "ImportBrick: TextEdit set to:" << textEdit;
}

void ImportBrick::importFile() {
    if (!textEdit) {
        qDebug() << "ImportBrick: No text edit set!";
        return;
    }

    DialogBrick dialog(this);
    QString filter = "Text (*.txt);;HTML (*.html);;Word (*.docx);;OpenDocument (*.odt);;PDF (*.pdf);;All Files (*)";
    QString fileName = dialog.getOpenFileName(nullptr, "Import File", "/home/ares/test", filter);
    if (fileName.isEmpty()) {
        qDebug() << "ImportBrick: No file selected";
        return;
    }

    QString ext = QFileInfo(fileName).suffix().toLower();
    qDebug() << "ImportBrick: Importing file:" << fileName << "with extension:" << ext;

    if (ext == "txt" || ext == "html" || ext == "docx" || ext == "odt" || ext == "pdf") {
        QString content = fileTranslator->importFile(fileName);
        if (content.isEmpty() && !textEdit->toPlainText().isEmpty()) {
            qDebug() << "ImportBrick: Import failed but textEdit updated anyway";
        } else if (!content.isEmpty()) {
            qDebug() << "ImportBrick: Successfully imported:" << fileName;
        }
    } else {
        qDebug() << "ImportBrick: Unsupported file format:" << ext;
        QMessageBox::warning(nullptr, "Unsupported Format", 
            "The file type ‘." + ext + "’ isn’t supported.\nTry .txt, .html, .docx, .odt, or .pdf.");
    }
}
