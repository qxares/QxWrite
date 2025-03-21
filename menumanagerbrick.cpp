#include "menumanagerbrick.h"
#include <QMenuBar>
#include <QAction>
#include <QDebug>
#include "insertbrick.h"
#include "savebrick.h"
#include "boldbrick.h"

MenuManagerBrick::MenuManagerBrick(QMenuBar *bar, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, QObject *parent)
    : QObject(parent), menuBar(bar), insertBrick(insert), saveBrick(save), boldBrick(bold) {
    qDebug() << "MenuManagerBrick initialized, menuBar:" << menuBar;
}

void MenuManagerBrick::setupMenus() {
    qDebug() << "Setting up menus...";
    if (!menuBar) {
        qDebug() << "No menu bar provided!";
        return;
    }
    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    QAction *saveAction = fileMenu->addAction(tr("Save"));
    connect(saveAction, &QAction::triggered, saveBrick, &SaveBrick::save);

    QMenu *insertMenu = menuBar->addMenu(tr("&Insert"));
    QAction *insertImageAction = insertMenu->addAction(tr("Insert Image"));
    connect(insertImageAction, &QAction::triggered, insertBrick, &InsertBrick::insertImage);

    QMenu *formatMenu = menuBar->addMenu(tr("&Format"));
    QAction *boldAction = formatMenu->addAction(tr("Bold"));
    connect(boldAction, &QAction::triggered, boldBrick, &BoldBrick::toggleBold);

    qDebug() << "Menus set up.";
}
