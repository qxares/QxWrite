#include "contextmenuhandler.h"
#include <QMenu>
#include <QDebug>
#include "filedialog.h"
#include "imageplaceholder.h"

ContextMenuHandler::ContextMenuHandler(ImageSceneManager *sceneManager, ImageResizer *resizer, ImageSelector *selector, QWidget *parent)
    : QObject(parent), sceneManager(sceneManager), resizer(resizer), selector(selector), parentWidget(parent) {}

void ContextMenuHandler::showContextMenu(const QPoint &pos) {
    qDebug() << "Context menu requested at" << pos;
    QMenu menu(parentWidget);
    QAction *insertImageAction = menu.addAction("Insert Image");
    QUrl imageUrl = selector->selectImage(pos);
    if (selector->isImageSelected()) {
        QAction *resizeImageAction = menu.addAction("Resize Image");
        QAction *selectedAction = menu.exec(parentWidget->mapToGlobal(pos));
        if (selectedAction == insertImageAction) {
            insertImage();
        } else if (selectedAction == resizeImageAction) {
            QGraphicsPixmapItem *item = sceneManager->getImageItem(imageUrl);
            if (item) {
                item->setSelected(true);
                resizer->startResizing(imageUrl, item, pos);
                qDebug() << "Resize selected for" << imageUrl;
            }
        }
    } else {
        if (menu.exec(parentWidget->mapToGlobal(pos)) == insertImageAction) {
            insertImage();
        }
    }
}

void ContextMenuHandler::insertImage() {
    FileDialog dialog(parentWidget, QDir::homePath(), FileDialog::Import);
    if (dialog.exec()) {
        QString fileName = dialog.getSelectedFile();
        if (!fileName.isEmpty()) {
            ImagePlaceholder placeholder(fileName);
            if (placeholder.isValid()) {
                QTextEdit *editor = qobject_cast<QTextEdit*>(parentWidget);
                if (editor) {
                    QTextCursor cursor = editor->textCursor();
                    QPixmap pixmap = QPixmap::fromImage(placeholder.getImage());
                    sceneManager->addImage(placeholder.getUrl(), pixmap, editor->cursorRect(cursor).topLeft());
                    cursor.insertText(" ");
                    qDebug() << "Inserted image at" << placeholder.getUrl() << "Size:" << pixmap.size();
                }
            } else {
                qDebug() << "Cannot load image:" << fileName;
            }
        }
    }
}
