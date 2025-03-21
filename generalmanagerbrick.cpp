#include "generalmanagerbrick.h"
#include <QMenuBar>
#include <QAction>
#include <QDebug>
#include "insertbrick.h"
#include "savebrick.h"

GeneralManagerBrick::GeneralManagerBrick(QObject *parent)
    : QObject(parent), menuBar(nullptr), insertBrick(nullptr), saveBrick(nullptr) {
    if (auto *window = qobject_cast<QMainWindow*>(parent)) {
        menuBar = window->menuBar();
    }
    qDebug() << "GeneralManagerBrick initialized, menuBar:" << menuBar;
}

void GeneralManagerBrick::initBricks() {
    qDebug() << "Initializing bricks...";
    if (!menuBar) {
        qDebug() << "No menu bar found!";
        return;
    }
    insertBrick = new InsertBrick(parent());
    saveBrick = new SaveBrick(parent());

    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    QAction *saveAction = fileMenu->addAction(tr("Save"));
    connect(saveAction, &QAction::triggered, saveBrick, &SaveBrick::save);

    QMenu *insertMenu = menuBar->addMenu(tr("&Insert"));
    QAction *insertImageAction = insertMenu->addAction(tr("Insert Image"));
    connect(insertImageAction, &QAction::triggered, insertBrick, &InsertBrick::insertImage);

    qDebug() << "Bricks initialized.";
}
