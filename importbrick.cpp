#include "importbrick.h"
#include "dialogbrick.h"
#include "htmlfilebrick.h"
#include "docxfilebrick.h"
#include "odtfilebrick.h"
#include <QTextEdit>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>

ImportBrick::ImportBrick(QTextEdit *textEdit, QObject *parent) 
    : QObject(parent), 
      textEdit(textEdit),
      htmlBrick(new HtmlFileBrick(textEdit, this)),
      docxBrick(new DocxFileBrick(textEdit, this)),
      odtBrick(new OdtFileBrick(textEdit, this)) {
    qDebug() << "ImportBrick initialized, target edit:" << textEdit;
}

void ImportBrick::setTextEdit(QTextEdit *edit) {
    textEdit = edit;
    htmlBrick->setTextEdit(edit);
    docxBrick->setTextEdit(edit);
    odtBrick->setTextEdit(edit);
    qDebug() << "ImportBrick: TextEdit set to:" << textEdit;
}

void ImportBrick::importFile() {
    if (!textEdit) {
        qDebug() << "ImportBrick: No text edit set!";
        return;
    }

    DialogBrick dialog(this);
    QString filter = "Text (*.txt);;HTML (*.html);;Word (*.docx);;OpenDocument (*.odt);;All Files (*)";
    QString fileName = dialog.getOpenFileName(nullptr, "Import File", "/home/ares/test", filter);
    if (fileName.isEmpty()) {
        qDebug() << "ImportBrick: No file selected";
        return;
    }

    QString ext = QFileInfo(fileName).suffix().toLower();
    qDebug() << "ImportBrick: Importing file:" << fileName << "with extension:" << ext;

    QString content;
    if (ext == "html") {
        content = htmlBrick->importFile(fileName);
    } else if (ext == "docx") {
        content = docxBrick->importFile(fileName);
    } else if (ext == "odt") {
        content = odtBrick->importFile(fileName);
    } else {
        qDebug() << "ImportBrick: Unsupported file format:" << ext;
        QMessageBox::warning(nullptr, "Unsupported Format", 
            "The file type ‘." + ext + "’ isn’t supported.\nTry .html, .docx, or .odt.");
    }

    if (!content.isEmpty()) {
        qDebug() << "ImportBrick: Successfully imported:" << fileName;
    } else {
        qDebug() << "ImportBrick: Import failed for:" << fileName;
    }
}
