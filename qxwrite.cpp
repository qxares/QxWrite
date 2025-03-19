#include "qxwrite.h"
#include "documenteditor.h"
#include <QMenuBar>
#include <QMdiSubWindow>
#include <QDebug>

QxWrite::QxWrite(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "QxWrite constructor starting...";
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);
    qDebug() << "MDI area created successfully.";
    setupMenus();
    resize(800, 600);
    qDebug() << "QxWrite constructor finished.";
}

void QxWrite::setupMenus() {
    qDebug() << "Setting up menus...";
    QMenu *fileMenu = menuBar()->addMenu("File");
    QAction *newAct = fileMenu->addAction("New");
    connect(newAct, &QAction::triggered, this, &QxWrite::newDocument);
    fileMenu->addAction("Open");
    fileMenu->addAction("Save");
    fileMenu->addSeparator();
    fileMenu->addAction("Exit", this, &QWidget::close);
    menuBar()->setVisible(true);
    qDebug() << "Menu bar is native:" << menuBar()->isNativeMenuBar();
    qDebug() << "Menu bar is visible:" << menuBar()->isVisible();
}

void QxWrite::newDocument() {
    QMdiSubWindow *subWindow = new QMdiSubWindow;
    DocumentEditor *editor = new DocumentEditor(subWindow);
    subWindow->setWidget(editor);
    mdiArea->addSubWindow(subWindow);
    subWindow->show();
    qDebug() << "New Document window created. Active subwindow:" << (mdiArea->activeSubWindow() == subWindow);
}
