#include "documenthandlerbrick.h"
#include "documentwindow.h"
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
    subWindow->show();
    mdiArea->tileSubWindows();  // Tile to ensure visibility
    qDebug() << "DocumentHandlerBrick: New document added, type:" << static_cast<int>(type);
}
