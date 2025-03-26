#include "documenthandlerbrick.h"
#include "documentwindow.h"
#include <QDebug>
#include <QMdiArea>
#include <QMdiSubWindow>

DocumentHandlerBrick::DocumentHandlerBrick(QWidget *parent) : QObject(parent) {
    mdiArea = qobject_cast<QMdiArea*>(parent->findChild<QMdiArea*>());
    if (!mdiArea) {
        qDebug() << "DocumentHandlerBrick: No QMdiArea found!";
    }
}

void DocumentHandlerBrick::newDocument(NewFileBrick::DocType type) {
    if (mdiArea) {
        DocumentWindow *docWindow = new DocumentWindow(nullptr);  // No parent yet
        docWindow->newFile(type);
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(docWindow);
        subWindow->setWindowTitle(type == NewFileBrick::Note ? "QxNote" : 
                                 type == NewFileBrick::Document ? "QxDocument" : "QxGrid");
        subWindow->show();
        qDebug() << "DocumentHandlerBrick: New document added, type:" << type;
    } else {
        qDebug() << "DocumentHandlerBrick: No MDI area to handle new document!";
    }
}
