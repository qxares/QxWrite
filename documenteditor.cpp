#include "documenteditor.h"
#include <QDebug>
#include <QTextCursor>
#include <QFont>
#include <QMenu>
#include <QContextMenuEvent>
#include <QMouseEvent>

DocumentEditor::DocumentEditor(QWidget *parent) : QTextEdit(parent), selector(this), positioner(this), resizer(this), resizing(false) {
    setAcceptRichText(true);
    setDocumentTitle("Untitled Document");
    document()->setDefaultFont(QFont("Times New Roman", 12));
    setMouseTracking(true);
    qDebug() << "Rich text enabled:" << acceptRichText();
}

void DocumentEditor::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    QAction *insertImageAction = menu.addAction("Insert Image");
    QUrl imageUrl = selector.selectImage(event->pos());
    if (selector.isImageSelected() && !resizing) {
        QAction *resizeImageAction = menu.addAction("Resize Image");
        QAction *selectedAction = menu.exec(event->globalPos());
        if (selectedAction == insertImageAction) {
            insertImage();
        } else if (selectedAction == resizeImageAction) {
            resizing = true;
            QRect rect = positioner.getImageRect(imageUrl, event->pos());
            if (!rect.isEmpty()) {
                resizer.startResizing(imageUrl, event->pos(), rect);
            }
        }
    } else {
        if (menu.exec(event->globalPos()) == insertImageAction) {
            insertImage();
        }
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

void DocumentEditor::mousePressEvent(QMouseEvent *event) {
    QTextEdit::mousePressEvent(event);
    if (event->button() == Qt::LeftButton && selector.isImageSelected() && !resizing) {
        QUrl imageUrl = selector.selectImage(event->pos());
        QRect rect = positioner.getImageRect(imageUrl, event->pos());
        if (!rect.isEmpty()) {
            resizing = true;
            resizer.startResizing(imageUrl, event->pos(), rect);
        }
    }
}

void DocumentEditor::mouseMoveEvent(QMouseEvent *event) {
    if (resizing && (event->buttons() & Qt::LeftButton)) {
        resizer.updateResizing(event->pos());
    }
    QTextEdit::mouseMoveEvent(event);
}

void DocumentEditor::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && resizing) {
        resizer.finishResizing();
        resizing = false;
    }
    QTextEdit::mouseReleaseEvent(event);
}
