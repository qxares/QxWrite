#include "documenthandlerbrick.h"
#include "documentwindow.h"
#include "openfilebrick.h"
#include <QDebug>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QMouseEvent>

DocumentHandlerBrick::DocumentHandlerBrick(QWidget *parent) : QObject(parent) {
    mdiArea = qobject_cast<QMdiArea*>(parent->findChild<QMdiArea*>());
    if (!mdiArea) {
        qDebug() << "DocumentHandlerBrick: No QMdiArea found!";
    } else {
        qDebug() << "DocumentHandlerBrick: QMdiArea hooked at:" << mdiArea;
    }
}

void DocumentHandlerBrick::newDocument(NewFileBrick::DocType type) {
    if (!mdiArea) {
        qDebug() << "DocumentHandlerBrick: No MDI area to handle new document!";
        return;
    }
    DocumentWindow *docWindow = new DocumentWindow(nullptr);  // No parent yet
    docWindow->newFile(type);
    QMdiSubWindow *subWindow = mdiArea->addSubWindow(docWindow);
    subWindow->setWindowTitle(type == NewFileBrick::Note ? "QxNote" : 
                             type == NewFileBrick::Document ? "QxDocument" : "QxGrid");
    subWindow->resize(400, 300);  // Default size for visibility

    // Connect the context menu signal
    connect(docWindow, &DocumentWindow::customContextMenuRequested, this, &DocumentHandlerBrick::showContextMenu);

    // Add to the appropriate list
    if (type == NewFileBrick::Document) {
        documentWindows.append(subWindow);
    } else if (type == NewFileBrick::Note) {
        noteWindows.append(subWindow);
    } else if (type == NewFileBrick::Sheet) {
        sheetWindows.append(subWindow);
    }

    subWindow->show();
    cascadeWindows(type);  // Cascade windows of this type
    qDebug() << "DocumentHandlerBrick: New document added, type:" << static_cast<int>(type);
}

void DocumentHandlerBrick::openDocument(OpenFile prettierBrick *openFileBrick) {
    if (!mdiArea) {
        qDebug() << "DocumentHandlerBrick: No MDI area to handle open document!";
        return;
    }
    DocumentWindow *docWindow = new DocumentWindow(nullptr);  // No parent yet
    docWindow->newFile(NewFileBrick::Document);  // Default to QxDocument for opened files
    QMdiSubWindow *subWindow = mdiArea->addSubWindow(docWindow);
    subWindow->setWindowTitle("QxDocument");
    subWindow->resize(400, 300);  // Default size for visibility

    // Connect the context menu signal
    connect(docWindow, &DocumentWindow::customContextMenuRequested, this, &DocumentHandlerBrick::showContextMenu);

    documentWindows.append(subWindow);  // Add to QxDocuments stack
    subWindow->show();
    cascadeWindows(NewFileBrick::Document);  // Cascade QxDocuments

    openFileBrick->setTextEdit(docWindow->getTextEdit());
    openFileBrick->openFile();
    qDebug() << "DocumentHandlerBrick: Opened document in new window";
}

void DocumentHandlerBrick::cascadeWindows(NewFileBrick::DocType type) {
    QList<QMdiSubWindow*> *windowList = nullptr;
    if (type == NewFileBrick::Document) {
        windowList = &documentWindows;
    } else if (type == NewFileBrick::Note) {
        windowList = &noteWindows;  // Fixed typo: ¬eWindows to noteWindows
    } else if (type == NewFileBrick::Sheet) {
        windowList = &sheetWindows;
    }

    if (!windowList || windowList->isEmpty()) {
        return;
    }

    const int offset = 30;  // Offset for cascading
    QMdiSubWindow *anchorWindow = mdiArea->activeSubWindow();
    if (!anchorWindow || !windowList->contains(anchorWindow)) {
        anchorWindow = windowList->first();  // Fallback to first window
    }
    int x = anchorWindow->pos().x();
    int y = anchorWindow->pos().y();

    for (QMdiSubWindow *window : *windowList) {
        if (window != anchorWindow) {  // Skip the anchor itself
            x += offset;
            y += offset;
            window->move(x, y);
        }
    }
}

void DocumentHandlerBrick::showContextMenu(QMdiSubWindow *subWindow, const QPoint &pos) {
    DocumentWindow *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget());
    if (!docWindow) {
        qDebug() << "DocumentHandlerBrick: No DocumentWindow found for context menu!";
        return;
    }
    QTextEdit *textEdit = docWindow->getTextEdit();

    QMenu contextMenu;
    // Add standard text edit actions from QTextEdit
    contextMenu.addAction("Undo", textEdit, &QTextEdit::undo)->setEnabled(textEdit->document()->isUndoAvailable());
    contextMenu.addAction("Redo", textEdit, &QTextEdit::redo)->setEnabled(textEdit->document()->isRedoAvailable());
    contextMenu.addSeparator();
    contextMenu.addAction("Cut", textEdit, &QTextEdit::cut)->setEnabled(textEdit->textCursor().hasSelection());
    contextMenu.addAction("Copy", textEdit, &QTextEdit::copy)->setEnabled(textEdit->textCursor().hasSelection());
    contextMenu.addAction("Paste", textEdit, &QTextEdit::paste)->setEnabled(QApplication::clipboard()->text().length() > 0);
    contextMenu.addSeparator();
    // Add custom "Move Cascade" action
    QAction *moveCascadeAction = contextMenu.addAction("Move Cascade", [this, subWindow]() { moveCascade(subWindow); });

    contextMenu.exec(subWindow->mapToGlobal(pos));
}

void DocumentHandlerBrick::moveCascade(QMdiSubWindow *subWindow) {
    QList<QMdiSubWindow*> *windowList = nullptr;
    NewFileBrick::DocType type;
    if (documentWindows.contains(subWindow)) {
        windowList = &documentWindows;
        type = NewFileBrick::Document;
    } else if (noteWindows.contains(subWindow)) {
        windowList = &noteWindows;  // Fixed typo: ¬eWindows to noteWindows
    } else if (sheetWindows.contains(subWindow)) {
        windowList = &sheetWindows;
        type = NewFileBrick::Sheet;
    }

    if (!windowList || windowList->isEmpty()) {
        return;
    }

    QPoint initialPos = QCursor::pos();
    QPoint originalAnchorPos = subWindow->pos();
    QApplication::setOverrideCursor(Qt::SizeAllCursor);  // Visual feedback

    // Wait for mouse press to start dragging
    while (!(QApplication::mouseButtons() & Qt::LeftButton)) {
        QApplication::processEvents();  // Keep UI responsive
    }

    while (QApplication::mouseButtons() & Qt::LeftButton) {
        QApplication::processEvents();
        QPoint currentPos = QCursor::pos();
        int dx = currentPos.x() - initialPos.x();
        int dy = currentPos.y() - initialPos.y();

        // Move the anchor window
        subWindow->move(originalAnchorPos.x() + dx, originalAnchorPos.y() + dy);

        // Move the rest of the cascade relative to the anchor
        int offset = 30;
        int x = subWindow->pos().x();
        int y = subWindow->pos().y();
        for (QMdiSubWindow *window : *windowList) {
            if (window != subWindow) {
                x += offset;
                y += offset;
                window->move(x, y);
            }
        }
    }

    QApplication::restoreOverrideCursor();
}
