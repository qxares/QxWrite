#include "menumanagerbrick.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>

MenuManagerBrick::MenuManagerBrick(QWidget *parent) : QObject(parent) {
    menuBar = new QMenuBar(parent);
    qDebug() << "MenuManagerBrick initialized, menuBar:" << menuBar;
    setupMenus();
}

QMenuBar* MenuManagerBrick::getMenuBar() {
    return menuBar;
}

void MenuManagerBrick::setupMenus() {
    QMenu *fileMenu = menuBar->addMenu("File");
    fileMenu->addAction("New");
    fileMenu->addAction("Open");
    fileMenu->addAction("Save");
    fileMenu->addSeparator();
    fileMenu->addAction("Exit");

    QMenu *editMenu = menuBar->addMenu("Edit");
    editMenu->addAction("Undo");
    editMenu->addAction("Redo");
    editMenu->addSeparator();
    editMenu->addAction("Cut");
    editMenu->addAction("Copy");
    editMenu->addAction("Paste");

    qDebug() << "Menus set up.";
}
