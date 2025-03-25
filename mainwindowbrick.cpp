#include "mainwindowbrick.h"
#include "documentwindow.h"
#include "toolbarbrick.h"
#include "menumanagerbrick.h"
#include <QDebug>

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "MainWindowBrick starting...";
    setupUI();
    qDebug() << "MainWindowBrick ready.";
}

MainWindowBrick::~MainWindowBrick() {
    delete toolbarBrick;
    delete menuManagerBrick;
    delete documentWindow;
}

void MainWindowBrick::setupUI() {
    toolbarBrick = new ToolBarBrick(this);
    addToolBar(toolbarBrick->getToolBar());

    menuManagerBrick = new MenuManagerBrick(this);
    setMenuBar(menuManagerBrick->getMenuBar());

    documentWindow = new DocumentWindow(this);
    setCentralWidget(documentWindow);

    // Connect "New" to clear the embedded DocumentWindow
    QAction *newAction = toolbarBrick->getAction("new");
    if (newAction) {
        disconnect(newAction, nullptr, nullptr, nullptr);  // Clear any old connections
        connect(newAction, &QAction::triggered, this, [=]() {
            qDebug() << "MainWindowBrick: Clearing current DocumentWindow for New";
            documentWindow->clear();
        });
    } else {
        qDebug() << "MainWindowBrick: New action not found";
    }

    // Connect "Open" to trigger open in the embedded DocumentWindow
    QAction *openAction = toolbarBrick->getAction("open");
    if (openAction) {
        disconnect(openAction, nullptr, nullptr, nullptr);  // Clear any old connections
        connect(openAction, &QAction::triggered, this, [=]() {
            qDebug() << "MainWindowBrick: Triggering Open in current DocumentWindow";
            OpenFileBrick *openBrick = documentWindow->findChild<OpenFileBrick*>();
            if (openBrick) {
                openBrick->openFile();
            } else {
                qDebug() << "MainWindowBrick: Failed to find OpenFileBrick in DocumentWindow";
            }
        });
    } else {
        qDebug() << "MainWindowBrick: Open action not found";
    }

    resize(800, 600);
}
