#include "documenteditor.h"
#include "filedialog.h"
#include <QDebug>
#include <QTextImageFormat>
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
            QImage image(fileName);
            if (image.isNull()) {
                qDebug() << "Cannot load image:" << fileName;
                return;
            }
            QTextCursor cursor = textCursor();
            QString placeholder = QString("placeholder://%1").arg(qrand() % 1000);
            document()->addResource(QTextDocument::ImageResource, QUrl(placeholder), image);
            QTextImageFormat format;
            format.setName(placeholder);
            format.setWidth(100);
            format.setHeight(117);
            cursor.insertImage(format);
            qDebug() << "Inserted image at" << placeholder << "Size:" << image.size();
        }
    }
}
