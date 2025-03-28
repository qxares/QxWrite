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
#include <QClipboard>

DocumentHandlerBrick::DocumentHandlerBrick(QWidget *parent) : QObject(parent) {
    mdiArea = qobject_cast<QMdiArea*>(parent->findChild<QMdiArea*>());
    if (!mdiArea) {
        qDebug() << "DocumentHandlerBrick: No QMdiArea found!";
    } else {
        qDebug() << "DocumentHandlerBrick: QMdiArea hooked at:" << mdiArea;
    }
}

QTextEdit* DocumentHandlerBrick::newDocument(NewFileBrick::DocType type) {
    if (!mdiArea) {
        qDebug() << "DocumentHandlerBrick: No MDI area to handle new document!";
        return nullptr;
    }
    DocumentWindow *docWindow = new DocumentWindow(nullptr);
    docWindow->newFile(type);
    QMdiSubWindow *subWindow = mdiArea->addSubWindow(docWindow);
    subWindow->setWindowTitle(type == NewFileBrick::Note ? "QxNote" : 
                             type == NewFileBrick::Document ? "QxDocument" : "QxGrid");
    subWindow->resize(400, 300);

    subWindow->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(subWindow, &QMdiSubWindow::customContextMenuRequested, this, 
            [this, subWindow](const QPoint &pos) { showContextMenu(subWindow, pos); });

    connect(subWindow, &QMdiSubWindow::destroyed, this, [this, subWindow, type]() {
        if (type == NewFileBrick::Document) {
            documentWindows.removeAll(subWindow);
        } else if (type == NewFileBrick::Note) {
            noteWindows.removeAll(subWindow);
        } else if (type == NewFileBrick::Sheet) {
            sheetWindows.removeAll(subWindow);
        }
        qDebug() << "DocumentHandlerBrick: Subwindow removed from list, type:" << static_cast<int>(type);
    });

    if (type == NewFileBrick::Document) {
        documentWindows.append(subWindow);
    } else if (type == NewFileBrick::Note) {
        noteWindows.append(subWindow);
    } else if (type == NewFileBrick::Sheet) {
        sheetWindows.append(subWindow);
    }

    subWindow->show();
    cascadeWindows(type);
    qDebug() << "DocumentHandlerBrick: New document added, type:" << static_cast<int>(type);
    return docWindow->getTextEdit();
}

void DocumentHandlerBrick::openDocument(OpenFileBrick *openFileBrick) {
    if (!mdiArea) {
        qDebug() << "DocumentHandlerBrick: No MDI area to handle open document!";
        return;
    }
    DocumentWindow *docWindow = new DocumentWindow(nullptr);
    docWindow->newFile(NewFileBrick::Document);
    QMdiSubWindow *subWindow = mdiArea->addSubWindow(docWindow);
    subWindow->setWindowTitle("QxDocument");
    subWindow->resize(400, 300);

    subWindow->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(subWindow, &QMdiSubWindow::customContextMenuRequested, this, 
            [this, subWindow](const QPoint &pos) { showContextMenu(subWindow, pos); });

    connect(subWindow, &QMdiSubWindow::destroyed, this, [this, subWindow]() {
        documentWindows.removeAll(subWindow);
        qDebug() << "DocumentHandlerBrick: Subwindow removed from list, type: Document";
    });

    documentWindows.append(subWindow);
    subWindow->show();
    cascadeWindows(NewFileBrick::Document);

    openFileBrick->setTextEdit(docWindow->getTextEdit());
    openFileBrick->openFile();
    qDebug() << "DocumentHandlerBrick: Opened document in new window";
}

void DocumentHandlerBrick::cascadeWindows(NewFileBrick::DocType type) {
    QList<QMdiSubWindow*> *windowList = nullptr;
    if (type == NewFileBrick::Document) {
        windowList = &documentWindows;
    } else if (type == NewFileBrick::Note) {
        windowList = &noteWindows; // Fixed typo
    } else if (type == NewFileBrick::Sheet) {
        windowList = &sheetWindows;
    }

    if (!windowList || windowList->isEmpty()) {
        qDebug() << "DocumentHandlerBrick: No windows to cascade for type:" << static_cast<int>(type);
        return;
    }

    const int offset = 30;
    QMdiSubWindow *anchorWindow = mdiArea->activeSubWindow();
    if (!anchorWindow || !windowList->contains(anchorWindow)) {
        anchorWindow = windowList->first();
        qDebug() << "DocumentHandlerBrick: Using first window as anchor:" << anchorWindow;
    } else {
        qDebug() << "DocumentHandlerBrick: Using active window as anchor:" << anchorWindow;
    }

    if (!anchorWindow) {
        qDebug() << "DocumentHandlerBrick: No valid anchor window for cascading!";
        return;
    }

    int x = anchorWindow->pos().x();
    int y = anchorWindow->pos().y();

    for (QMdiSubWindow *window : *windowList) {
        if (window != anchorWindow) {
            x += offset;
            y += offset;
            window->move(x, y);
        }
    }
    qDebug() << "DocumentHandlerBrick: Cascaded" << windowList->size() << "windows for type:" << static_cast<int>(type);
}

void DocumentHandlerBrick::showContextMenu(QMdiSubWindow *subWindow, const QPoint &pos) {
    DocumentWindow *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget());
    if (!docWindow) {
        qDebug() << "DocumentHandlerBrick: No DocumentWindow found for context menu!";
        return;
    }
    QTextEdit *textEdit = docWindow->getTextEdit();
    if (!textEdit) {
        qDebug() << "DocumentHandlerBrick: No textEdit in DocumentWindow!";
        return;
    }

    QMenu contextMenu;
    contextMenu.addAction("Undo", textEdit, &QTextEdit::undo)->setEnabled(textEdit->document()->isUndoAvailable());
    contextMenu.addAction("Redo", textEdit, &QTextEdit::redo)->setEnabled(textEdit->document()->isRedoAvailable());
    contextMenu.addSeparator();
    contextMenu.addAction("Cut", textEdit, &QTextEdit::cut)->setEnabled(textEdit->textCursor().hasSelection());
    contextMenu.addAction("Copy", textEdit, &QTextEdit::copy)->setEnabled(textEdit->textCursor().hasSelection());
    contextMenu.addAction("Paste", textEdit, &QTextEdit::paste)->setEnabled(QApplication::clipboard()->text().length() > 0);
    contextMenu.addSeparator();
    contextMenu.addAction("Move Cascade", [this, subWindow]() { moveCascade(subWindow); });

    contextMenu.exec(subWindow->mapToGlobal(pos));
    qDebug() << "DocumentHandlerBrick: Context menu shown for subWindow:" << subWindow;
}

void DocumentHandlerBrick::moveCascade(QMdiSubWindow *subWindow) {
    QList<QMdiSubWindow*> *windowList = nullptr;
    if (documentWindows.contains(subWindow)) {
        windowList = &documentWindows;
    } else if (noteWindows.contains(subWindow)) {
        windowList = &noteWindows; // Fixed typo
    } else if (sheetWindows.contains(subWindow)) {
        windowList = &sheetWindows;
    }

    if (!windowList || windowList->isEmpty()) {
        qDebug() << "DocumentHandlerBrick: No windows to move in cascade for subWindow:" << subWindow;
        return;
    }

    qDebug() << "DocumentHandlerBrick: Moving cascade of" << windowList->size() << "windows, anchor:" << subWindow;

    QPoint initialPos = QCursor::pos();
    QPoint originalAnchorPos = subWindow->pos();
    QApplication::setOverrideCursor(Qt::SizeAllCursor);

    while (!(QApplication::mouseButtons() & Qt::LeftButton)) {
        QApplication::processEvents();
    }

    while (QApplication::mouseButtons() & Qt::LeftButton) {
        QApplication::processEvents();
        QPoint currentPos = QCursor::pos();
        int dx = currentPos.x() - initialPos.x();
        int dy = currentPos.y() - initialPos.y();

        subWindow->move(originalAnchorPos.x() + dx, originalAnchorPos.y() + dy);
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
    qDebug() << "DocumentHandlerBrick: Cascade moved, new anchor pos:" << subWindow->pos();
}
