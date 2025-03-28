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
    if (openAction) {
        QAction *menuOpen = new QAction("Open", this);       // Clone, no icon
        menuOpen->setToolTip(openAction->toolTip());
        fileMenu->addAction(menuOpen);
        QObject::connect(menuOpen, &QAction::triggered, openAction, &QAction::trigger);
    }
    if (saveAction) {
        QAction *menuSave = new QAction("Save", this);       // Clone, no icon
        menuSave->setToolTip(saveAction->toolTip());
        fileMenu->addAction(menuSave);
        QObject::connect(menuSave, &QAction::triggered, saveAction, &QAction::trigger);
    }
    if (boldAction) {
        QAction *menuBold = new QAction("Bold", this);       // Clone, no icon
        menuBold->setToolTip(boldAction->toolTip());
        formatMenu->addAction(menuBold);
        QObject::connect(menuBold, &QAction::triggered, boldAction, &QAction::trigger);
    }
    if (italicAction) {
        QAction *menuItalic = new QAction("Italic", this);   // Clone, no icon
        menuItalic->setToolTip(italicAction->toolTip());
        formatMenu->addAction(menuItalic);
        QObject::connect(menuItalic, &QAction::triggered, italicAction, &QAction::trigger);
    }
    if (fontAction) {
        QAction *menuFont = new QAction("Font", this);       // Clone, no icon
        menuFont->setToolTip(fontAction->toolTip());
        formatMenu->addAction(menuFont);
        QObject::connect(menuFont, &QAction::triggered, fontAction, &QAction::trigger);
    }
    if (colorAction) {
        QAction *menuColor = new QAction("Color", this);     // Clone, no icon
        menuColor->setToolTip(colorAction->toolTip());
        formatMenu->addAction(menuColor);
        QObject::connect(menuColor, &QAction::triggered, colorAction, &QAction::trigger);
    }
    if (imageAction) {
        QAction *menuImage = new QAction("Image", this);     // Clone, no icon
        menuImage->setToolTip(imageAction->toolTip());
        editMenu->addAction(menuImage);
        QObject::connect(menuImage, &QAction::triggered, imageAction, &QAction::trigger);
    }
    formatMenu->addSeparator();
    if (alignLeftAction) {
        QAction *menuAlignLeft = new QAction("Align Left", this);     // Clone, no icon
        menuAlignLeft->setToolTip(alignLeftAction->toolTip());
        formatMenu->addAction(menuAlignLeft);
        QObject::connect(menuAlignLeft, &QAction::triggered, alignLeftAction, &QAction::trigger);
    }
    if (alignCenterAction) {
        QAction *menuAlignCenter = new QAction("Align Center", this); // Clone, no icon
        menuAlignCenter->setToolTip(alignCenterAction->toolTip());
        formatMenu->addAction(menuAlignCenter);
        QObject::connect(menuAlignCenter, &QAction::triggered, alignCenterAction, &QAction::trigger);
    }
    if (alignRightAction) {
        QAction *menuAlignRight = new QAction("Align Right", this);   // Clone, no icon
        menuAlignRight->setToolTip(alignRightAction->toolTip());
        formatMenu->addAction(menuAlignRight);
        QObject::connect(menuAlignRight, &QAction::triggered, alignRightAction, &QAction::trigger);
    }

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
