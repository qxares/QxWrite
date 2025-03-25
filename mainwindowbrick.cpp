#include "mainwindowbrick.h"
#include "documentwindow.h"
#include <QDebug>

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "MainWindowBrick starting...";
    setupUI();
    qDebug() << "MainWindowBrick ready.";
}

MainWindowBrick::~MainWindowBrick() {
    delete toolbarBrick;
    delete menuManagerBrick;
}

void MainWindowBrick::setupUI() {
    toolbarBrick = new ToolBarBrick(this);
    addToolBar(toolbarBrick->getToolBar());

    menuManagerBrick = new MenuManagerBrick(this);
    setMenuBar(menuManagerBrick->getMenuBar());

    // Connect "New" to spawn a new DocumentWindow
    connect(toolbarBrick->getAction("new"), &QAction::triggered, this, [=]() {
        qDebug() << "MainWindowBrick: Spawning new DocumentWindow";
        DocumentWindow *doc = new DocumentWindow(nullptr);  // Independent window
        doc->show();
    });

    // Connect "Open" to spawn a new DocumentWindow and trigger open
    connect(toolbarBrick->getAction("open"), &QAction::triggered, this, [=]() {
        qDebug() << "MainWindowBrick: Spawning DocumentWindow for Open";
        DocumentWindow *doc = new DocumentWindow(nullptr);  // Independent window
        doc->show();
        OpenFileBrick *openBrick = doc->findChild<OpenFileBrick*>();
        if (openBrick) {
            openBrick->openFile();
        } else {
            qDebug() << "MainWindowBrick: Failed to find OpenFileBrick in DocumentWindow";
        }
    });

    resize(400, 300);
}
