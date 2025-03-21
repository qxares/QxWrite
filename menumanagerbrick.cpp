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
    : QObject(parent), menuBar(bar), insertBrick(insert), saveBrick(save), boldBrick(bold), newFileBrick(newFile), italicBrick(italic), boldAction(nullptr), italicAction(nullptr) {
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
    boldAction = formatMenu->addAction(tr("Bold"));
    boldAction->setCheckable(true);
    connect(boldAction, &QAction::toggled, boldBrick, &BoldBrick::toggleBold);
    connect(boldBrick, &BoldBrick::boldToggled, boldAction, &QAction::setChecked);

    italicAction = formatMenu->addAction(tr("Italic"));
    italicAction->setCheckable(true);
    connect(italicAction, &QAction::toggled, italicBrick, &ItalicBrick::toggleItalic);
    connect(italicBrick, &ItalicBrick::italicToggled, italicAction, &QAction::setChecked);

    connect(newFileBrick, &NewFileBrick::newFileCreated, this, &MenuManagerBrick::updateToggleStates);
    updateToggleStates();

    qDebug() << "Menus set up.";
}

void MenuManagerBrick::updateToggleStates() {
    boldAction->setChecked(false);
    italicAction->setChecked(false);
}
