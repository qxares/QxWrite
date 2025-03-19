#include "documenteditor.h"
#include <QDebug>
#include <QTextCursor>
#include <QFont>
#include <QMenu>
#include <QContextMenuEvent>

DocumentEditor::DocumentEditor(QWidget *parent) : QTextEdit(parent) {
    setAcceptRichText(true);
    setDocumentTitle("Untitled Document");
    document()->setDefaultFont(QFont("Times New Roman", 12));
    qDebug() << "Rich text enabled:" << acceptRichText();
}

void DocumentEditor::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    QAction *insertImageAction = menu.addAction("Insert Image");
    if (menu.exec(event->globalPos()) == insertImageAction) {
        insertImage();
    }
}

void DocumentEditor::insertImage() {
    FileDialog dialog(this, QDir::homePath(), FileDialog::Import);
    if (dialog.exec()) {
        QString fileName = dialog.getSelectedFile();
        if (!fileName.isEmpty()) {
            ImagePlaceholder placeholder(fileName);
            if (placeholder.isValid()) {
                QTextCursor cursor = textCursor();
                document()->addResource(QTextDocument::ImageResource, placeholder.getUrl(), placeholder.getImage());
                cursor.insertImage(placeholder.getFormat());
                qDebug() << "Inserted image at" << placeholder.getUrl() << "Size:" << placeholder.getImage().size();
            } else {
                qDebug() << "Cannot load image:" << fileName;
            }
        }
    }
}
