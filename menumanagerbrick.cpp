#include "menumanagerbrick.h"
#include <QMenuBar>
#include <QAction>
#include <QDebug>
#include "insertbrick.h"
#include "savebrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"

MenuManagerBrick::MenuManagerBrick(QMenuBar *bar, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, QObject *parent)
    : QObject(parent), menuBar(bar), insertBrick(insert), saveBrick(save), boldBrick(bold), newFileBrick(newFile), italicBrick(italic) {
    qDebug() << "MenuManagerBrick initialized, menuBar:" << menuBar;
}

void MenuManagerBrick::setupMenus() {
    qDebug() << "Setting up menus...";
    if (!menuBar) {
        qDebug() << "No menu bar provided!";
        return;
    }
    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    QAction *newAction = fileMenu->addAction(tr("New"));
    connect(newAction, &QAction::triggered, newFileBrick, &NewFileBrick::newFile);
    QAction *saveAction = fileMenu->addAction(tr("Save"));
    connect(saveAction, &QAction::triggered, saveBrick, &SaveBrick::save);

    QMenu *insertMenu = menuBar->addMenu(tr("&Insert"));
    QAction *insertImageAction = insertMenu->addAction(tr("Insert Image"));
    connect(insertImageAction, &QAction::triggered, insertBrick, &InsertBrick::insertImage);

    QMenu *formatMenu = menuBar->addMenu(tr("&Format"));
    QAction *boldAction = formatMenu->addAction(tr("Bold"));
    connect(boldAction, &QAction::triggered, boldBrick, &BoldBrick::toggleBold);
    QAction *italicAction = formatMenu->addAction(tr("Italic"));
    connect(italicAction, &QAction::triggered, italicBrick, &ItalicBrick::toggleItalic);

    qDebug() << "Menus set up.";
}
