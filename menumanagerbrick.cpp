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
    QMenu *newMenu = fileMenu->addMenu(QIcon(":/icons/icons/file-plus.svg"), "New");
    QAction *newNote = newMenu->addAction(QIcon(":/icons/icons/file-plus.svg"), "QxNote");
    QAction *newDoc = newMenu->addAction(QIcon(":/icons/icons/file-plus.svg"), "QxDocument");
    QAction *newSheet = newMenu->addAction(QIcon(":/icons/icons/file-plus.svg"), "QxSheet");

    QAction *saveAsAction = fileMenu->addAction(QIcon(":/icons/icons/save-as.svg"), "Save As");
    if (openAction) fileMenu->addAction(openAction);
    if (saveAction) fileMenu->addAction(saveAction);
    if (boldAction) formatMenu->addAction(boldAction);
    if (italicAction) formatMenu->addAction(italicAction);
    if (fontAction) formatMenu->addAction(fontAction);
    if (colorAction) formatMenu->addAction(colorAction);
    if (imageAction) editMenu->addAction(imageAction);
    formatMenu->addSeparator();
    if (alignLeftAction) formatMenu->addAction(alignLeftAction);
    if (alignCenterAction) formatMenu->addAction(alignCenterAction);
    if (alignRightAction) formatMenu->addAction(alignRightAction);

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
