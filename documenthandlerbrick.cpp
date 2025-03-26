#include "documenthandlerbrick.h"
#include "documentwindow.h"
#include "openfilebrick.h"
#include <QDebug>
#include <QMdiArea>
#include <QMdiSubWindow>

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

void DocumentHandlerBrick::openDocument(OpenFileBrick *openFileBrick) {
    if (!mdiArea) {
        qDebug() << "DocumentHandlerBrick: No MDI area to handle open document!";
        return;
    }
    DocumentWindow *docWindow = new DocumentWindow(nullptr);  // No parent yet
    docWindow->newFile(NewFileBrick::Document);  // Default to QxDocument for opened files
    QMdiSubWindow *subWindow = mdiArea->addSubWindow(docWindow);
    subWindow->setWindowTitle("QxDocument");
    subWindow->resize(400, 300);  // Default size for visibility

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
        windowList = &noteWindows;  // Fixed typo from your output
    } else if (type == NewFileBrick::Sheet) {
        windowList = &sheetWindows;
    }

    if (!windowList || windowList->isEmpty()) {
        return;
    }

    const int offset = 30;  // Offset for cascading
    // Use active window if available, otherwise first window as anchor
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
