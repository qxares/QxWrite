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

    // Connect toolbar "New" to clear the embedded DocumentWindow
    QAction *newAction = toolbarBrick->getAction("new");
    if (newAction) {
        disconnect(newAction, nullptr, nullptr, nullptr);
        connect(newAction, &QAction::triggered, this, [=]() {
            qDebug() << "MainWindowBrick: Clearing current DocumentWindow for New (Toolbar)";
            documentWindow->clear();
        });
    } else {
        qDebug() << "MainWindowBrick: Toolbar New action not found";
    }

    // Connect toolbar "Open" to trigger open in the embedded DocumentWindow
    QAction *openAction = toolbarBrick->getAction("open");
    if (openAction) {
        disconnect(openAction, nullptr, nullptr, nullptr);
        connect(openAction, &QAction::triggered, this, [=]() {
            qDebug() << "MainWindowBrick: Triggering Open in current DocumentWindow (Toolbar)";
            OpenFileBrick *openBrick = documentWindow->findChild<OpenFileBrick*>();
            if (openBrick) {
                openBrick->openFile();
            } else {
                qDebug() << "MainWindowBrick: Failed to find OpenFileBrick in DocumentWindow";
            }
        });
    } else {
        qDebug() << "MainWindowBrick: Toolbar Open action not found";
    }

    // Override menu "New" and "Open" actions
    QList<QAction*> menuActions = menuManagerBrick->getMenuBar()->findChildren<QAction*>();
    for (QAction *action : menuActions) {
        if (action->text() == "New") {
            disconnect(action, nullptr, nullptr, nullptr);
            connect(action, &QAction::triggered, this, [=]() {
                qDebug() << "MainWindowBrick: Clearing current DocumentWindow for New (Menu)";
                documentWindow->clear();
            });
        } else if (action->text() == "Open") {
            disconnect(action, nullptr, nullptr, nullptr);
            connect(action, &QAction::triggered, this, [=]() {
                qDebug() << "MainWindowBrick: Triggering Open in current DocumentWindow (Menu)";
                OpenFileBrick *openBrick = documentWindow->findChild<OpenFileBrick*>();
                if (openBrick) {
                    openBrick->openFile();
                } else {
                    qDebug() << "MainWindowBrick: Failed to find OpenFileBrick in DocumentWindow";
                }
            });
        }
    }

    resize(800, 600);
}
