#include "menumanagerbrick.h"
#include "iconbrick.h"
#include <QMenuBar>
#include <QMenu>
#include <QDebug>

MenuManagerBrick::MenuManagerBrick(QWidget *parent) : QObject(parent) {
    menuBar = new QMenuBar(parent);
    iconBrick = new IconBrick(this);
    qDebug() << "MenuManagerBrick initialized, menuBar:" << menuBar;

    setupMenus();
}

QMenuBar* MenuManagerBrick::getMenuBar() {
    return menuBar;
}

void MenuManagerBrick::setupMenus() {
    QMenu *fileMenu = menuBar->addMenu("File");
    fileMenu->addAction(iconBrick->getIcon("new"), "New");
    fileMenu->addAction(iconBrick->getIcon("open"), "Open");
    fileMenu->addAction(iconBrick->getIcon("save"), "Save");
    fileMenu->addSeparator();
    fileMenu->addAction("Exit", qApp, &QApplication::quit);

    QMenu *editMenu = menuBar->addMenu("Edit");
    editMenu->addAction("Undo");
    editMenu->addAction("Redo");
    editMenu->addSeparator();
    editMenu->addAction("Cut");
    editMenu->addAction("Copy");
    editMenu->addAction("Paste");

    qDebug() << "Menus set up.";
}
