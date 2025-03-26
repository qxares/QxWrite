#include "newfilebrick.h"
#include <QTextEdit>
#include <QDebug>

NewFileBrick::NewFileBrick(QTextEdit *edit, QObject *parent) 
    : QObject(parent), targetEdit(edit) {
    qDebug() << "NewFileBrick initialized, target edit:" << targetEdit;
}

void NewFileBrick::newFile(DocType type) {
    qDebug() << "NewFileBrick: Creating new document, type:" << type;
    targetEdit->clear();
    switch (type) {
        case Note:
            targetEdit->setDocumentTitle("Untitled Note");
            targetEdit->setAcceptRichText(false);  // Plain text
            break;
        case Document:
            targetEdit->setDocumentTitle("Untitled Document");
            targetEdit->setAcceptRichText(true);   // Rich text
            break;
        case Sheet:
            targetEdit->setDocumentTitle("Untitled Sheet");
            targetEdit->setReadOnly(true);         // Placeholder—Sheet needs QTableWidget later
            targetEdit->setPlainText("Spreadsheet placeholder—QTableWidget TBD");
            break;
    }
}
