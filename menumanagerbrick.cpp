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

void MenuManagerBrick::setupMenus(QAction *openAction, QAction *saveAction,
                                  QAction *boldAction, QAction *italicAction, QAction *fontAction,
                                  QAction *colorAction, QAction *imageAction, QAction *alignLeftAction,
                                  QAction *alignCenterAction, QAction *alignRightAction) {
    QAction *newActionMenu = fileMenu->addAction("New");  // No icon
    QMenu *newMenu = new QMenu();
    QAction *newNote = newMenu->addAction("QxNote");      // No icon
    QAction *newDoc = newMenu->addAction("QxDocument");   // No icon
    QAction *newSheet = newMenu->addAction("QxSheet");    // No icon
    newActionMenu->setMenu(newMenu);

    QAction *saveAsAction = fileMenu->addAction("Save As");  // No icon
    if (openAction) fileMenu->addAction(openAction);         // Keeps toolbar icon
    if (saveAction) fileMenu->addAction(saveAction);         // Keeps toolbar icon
    if (boldAction) formatMenu->addAction(boldAction);       // Keeps toolbar icon
    if (italicAction) formatMenu->addAction(italicAction);   // Keeps toolbar icon
    if (fontAction) formatMenu->addAction(fontAction);       // Keeps toolbar icon
    if (colorAction) formatMenu->addAction(colorAction);     // Keeps toolbar icon
    if (imageAction) editMenu->addAction(imageAction);       // Keeps toolbar icon
    formatMenu->addSeparator();
    if (alignLeftAction) formatMenu->addAction(alignLeftAction);     // Keeps toolbar icon
    if (alignCenterAction) formatMenu->addAction(alignCenterAction); // Keeps toolbar icon
    if (alignRightAction) formatMenu->addAction(alignRightAction);   // Keeps toolbar icon

    QObject::connect(newNote, &QAction::triggered, this, [this]() { emit newFileTriggered(0); });
    QObject::connect(newDoc, &QAction::triggered, this, [this]() { emit newFileTriggered(1); });
    QObject::connect(newSheet, &QAction::triggered, this, [this]() { emit newFileTriggered(2); });
    QObject::connect(saveAsAction, &QAction::triggered, this, [this]() { emit saveAsTriggered(); });

    qDebug() << "Menus set up.";
}

QMenuBar* MenuManagerBrick::getMenuBar() const {
    return menuBar;
}

MenuManagerBrick::~MenuManagerBrick() {}
