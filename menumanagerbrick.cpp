#include "menumanagerbrick.h"
#include <QMenuBar>
#include <QMenu>
#include <QDebug>

MenuManagerBrick::MenuManagerBrick(QWidget *parent) : QObject(parent) {
    menuBar = new QMenuBar(parent);
    fileMenu = new QMenu("File", menuBar);
    editMenu = new QMenu("Edit", menuBar);
    formatMenu = new QMenu("Format", menuBar);
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);
    menuBar->addMenu(formatMenu);
    qDebug() << "MenuManagerBrick initialized, menuBar:" << menuBar;
}

void MenuManagerBrick::setupMenus(QAction *newAction, QAction *openAction, QAction *saveAction,
                                  QAction *boldAction, QAction *italicAction, QAction *fontAction,
                                  QAction *colorAction, QAction *imageAction, QAction *alignLeftAction,
                                  QAction *alignCenterAction, QAction *alignRightAction) {
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    formatMenu->addAction(boldAction);
    formatMenu->addAction(italicAction);
    formatMenu->addAction(fontAction);
    formatMenu->addAction(colorAction);
    editMenu->addAction(imageAction);
    formatMenu->addSeparator();
    formatMenu->addAction(alignLeftAction);
    formatMenu->addAction(alignCenterAction);
    formatMenu->addAction(alignRightAction);

    qDebug() << "Menus set up.";
}

QMenuBar* MenuManagerBrick::getMenuBar() const {
    return menuBar;
}
