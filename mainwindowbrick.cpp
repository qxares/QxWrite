#include "mainwindowbrick.h"
#include "documentwindow.h"
#include "toolbarbrick.h"
#include "menumanagerbrick.h"
#include "newfilebrick.h"
#include "openfilebrick.h"
#include <QAction>
#include <QMenuBar>
#include <QList>
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

    // NewFileBrick setup
    NewFileBrick *newFileBrick = documentWindow->findChild<NewFileBrick*>();
    if (!newFileBrick) {
        qDebug() << "MainWindowBrick: Failed to find NewFileBrick in DocumentWindow";
        return;
    }

    // Connect toolbar "New"
    QAction *newAction = toolbarBrick->getAction("new");
    if (newAction) {
        QObject::disconnect(newAction, &QAction::triggered, nullptr, nullptr);
        connect(newAction, &QAction::triggered, newFileBrick, &NewFileBrick::newFile);
    } else {
        qDebug() << "MainWindowBrick: Toolbar New action not found";
    }

    // Connect menu "New" and "Open"
    QList<QAction*> menuActions = menuManagerBrick->getMenuBar()->findChildren<QAction*>();
    for (QAction *action : menuActions) {
        if (action->text() == "New") {
            QObject::disconnect(action, &QAction::triggered, nullptr, nullptr);
            connect(action, &QAction::triggered, newFileBrick, &NewFileBrick::newFile);
        } else if (action->text() == "Open") {
            QObject::disconnect(action, &QAction::triggered, nullptr, nullptr);
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
