#include "menumanagerbrick.h"
#include <QMenuBar>
#include <QMenu>
#include <QDebug>
#include <QAction>
#include <QWidgetAction>
#include <QComboBox>

MenuManagerBrick::MenuManagerBrick(QWidget *parent) : QObject(parent) {
    menuBar = new QMenuBar(parent);
    fileMenu = new QMenu("File", menuBar);
    editMenu = new QMenu("Edit", menuBar);
    formatMenu = new QMenu("Format", menuBar);
    tableMenu = new QMenu("Table", menuBar);
    toolsMenu = new QMenu("Tools", menuBar);
    helpMenu = new QMenu("Help", menuBar);
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);
    menuBar->addMenu(formatMenu);
    menuBar->addMenu(tableMenu);
    menuBar->addMenu(toolsMenu);
    menuBar->addMenu(helpMenu);
    qDebug() << "MenuManagerBrick initialized, menuBar:" << menuBar;
}

void MenuManagerBrick::setupMenus(QAction *openAction, QAction *saveAction,
                                  QAction *boldAction, QAction *italicAction, QAction *fontAction,
                                  QAction *colorAction, QAction *imageAction, QAction *alignLeftAction,
                                  QAction *alignCenterAction, QAction *alignRightAction,
                                  QAction *tableAction, QAction *translateAction) {
    QAction *newActionMenu = fileMenu->addAction("New");
    QMenu *newMenu = new QMenu();
    QAction *newNote = newMenu->addAction("QxNote");
    QAction *newDoc = newMenu->addAction("QxDocument");
    QAction *newSheet = newMenu->addAction("QxSheet");
    newActionMenu->setMenu(newMenu);

    QAction *importAction = fileMenu->addAction("Import");
    QAction *exportAction = fileMenu->addAction("Export");
    QAction *saveAsAction = fileMenu->addAction("Save As");
    QAction *exitAction = fileMenu->addAction("Exit");

    if (openAction) {
        QAction *menuOpen = new QAction("Open", this);
        menuOpen->setToolTip(openAction->toolTip());
        fileMenu->addAction(menuOpen);
        QObject::connect(menuOpen, &QAction::triggered, openAction, &QAction::trigger);
    }
    if (saveAction) {
        QAction *menuSave = new QAction("Save", this);
        menuSave->setToolTip(saveAction->toolTip());
        fileMenu->addAction(menuSave);
        QObject::connect(menuSave, &QAction::triggered, saveAction, &QAction::trigger);
    }

    QMenu *insertMenu = new QMenu("Insert", editMenu);
    editMenu->addMenu(insertMenu);
    if (imageAction) {
        QAction *menuImage = new QAction("Image", this);
        menuImage->setToolTip(imageAction->toolTip());
        insertMenu->addAction(menuImage);
        QObject::connect(menuImage, &QAction::triggered, this, &MenuManagerBrick::insertImageTriggered);
    }

    if (boldAction) {
        QAction *menuBold = new QAction("Bold", this);
        menuBold->setToolTip(boldAction->toolTip());
        formatMenu->addAction(menuBold);
        QObject::connect(menuBold, &QAction::triggered, boldAction, &QAction::trigger);
    }
    if (italicAction) {
        QAction *menuItalic = new QAction("Italic", this);
        menuItalic->setToolTip(italicAction->toolTip());
        formatMenu->addAction(menuItalic);
        QObject::connect(menuItalic, &QAction::triggered, italicAction, &QAction::trigger);
    }
    if (fontAction) {
        QAction *menuFont = new QAction("Font", this);
        menuFont->setToolTip(fontAction->toolTip());
        formatMenu->addAction(menuFont);
        QObject::connect(menuFont, &QAction::triggered, fontAction, &QAction::trigger);
    }
    if (colorAction) {
        QAction *menuColor = new QAction("Color", this);
        menuColor->setToolTip(colorAction->toolTip());
        formatMenu->addAction(menuColor);
        QObject::connect(menuColor, &QAction::triggered, colorAction, &QAction::trigger);
    }

    if (tableAction) {
        QAction *insertTable = new QAction("Insert Table", this);
        insertTable->setToolTip("Insert a table");
        tableMenu->addAction(insertTable);
        QObject::connect(insertTable, &QAction::triggered, this, &MenuManagerBrick::insertTableTriggered);
    }

    QMenu *rowMenu = new QMenu("Row", tableMenu);
    QAction *insertRowAbove = rowMenu->addAction("Insert Above");
    QAction *insertRowBelow = rowMenu->addAction("Insert Below");
    tableMenu->addMenu(rowMenu);

    QMenu *columnMenu = new QMenu("Column", tableMenu);
    QAction *insertColumnBefore = columnMenu->addAction("Insert Before");
    QAction *insertColumnAfter = columnMenu->addAction("Insert After");
    tableMenu->addMenu(columnMenu);

    QMenu *deleteMenu = new QMenu("Delete", tableMenu);
    QAction *deleteRow = deleteMenu->addAction("Selected Row");
    QAction *deleteColumn = deleteMenu->addAction("Selected Column");
    QAction *deleteTable = deleteMenu->addAction("Table");
    tableMenu->addMenu(deleteMenu);

    QAction *mergeCells = tableMenu->addAction("Merge Cells");
    QAction *splitCells = tableMenu->addAction("Split Cells");

    QMenu *alignMenu = new QMenu("Align Table", tableMenu);
    QAction *alignTableLeft = alignMenu->addAction("Left");
    QAction *alignTableCenter = alignMenu->addAction("Center");
    QAction *alignTableRight = alignMenu->addAction("Right");
    tableMenu->addMenu(alignMenu);

    QMenu *translateMenu = new QMenu("Translate To", toolsMenu);
    toolsMenu->addMenu(translateMenu);
    if (translateAction) {
        QWidgetAction *comboAction = new QWidgetAction(translateMenu);
        comboAction->setDefaultWidget(translateAction->data().value<QComboBox*>());
        translateMenu->addAction(comboAction);
        QObject::connect(translateAction, &QAction::triggered, this, &MenuManagerBrick::translateTriggered);
    }

    QAction *aboutAction = helpMenu->addAction("About");
    QObject::connect(aboutAction, &QAction::triggered, this, &MenuManagerBrick::aboutTriggered);

    QAction *menuNumbering = new QAction("Numbering", this);
    menuNumbering->setToolTip("Toggle numbered list");
    formatMenu->addAction(menuNumbering);
    QObject::connect(menuNumbering, &QAction::triggered, this, &MenuManagerBrick::numberingTriggered);

    QAction *menuBullets = new QAction("Bullets", this);
    menuBullets->setToolTip("Toggle bulleted list");
    formatMenu->addAction(menuBullets);
    QObject::connect(menuBullets, &QAction::triggered, this, &MenuManagerBrick::bulletsTriggered);

    if (alignLeftAction) {
        QAction *menuAlignLeft = new QAction("Align Left", this);
        menuAlignLeft->setToolTip(alignLeftAction->toolTip());
        formatMenu->addAction(menuAlignLeft);
        QObject::connect(menuAlignLeft, &QAction::triggered, alignLeftAction, &QAction::trigger);
    }
    if (alignCenterAction) {
        QAction *menuAlignCenter = new QAction("Align Center", this);
        menuAlignCenter->setToolTip(alignCenterAction->toolTip());
        formatMenu->addAction(menuAlignCenter);
        QObject::connect(menuAlignCenter, &QAction::triggered, alignCenterAction, &QAction::trigger);
    }
    if (alignRightAction) {
        QAction *menuAlignRight = new QAction("Align Right", this);
        menuAlignRight->setToolTip(alignRightAction->toolTip());
        formatMenu->addAction(menuAlignRight);
        QObject::connect(menuAlignRight, &QAction::triggered, alignRightAction, &QAction::trigger);
    }

    QObject::connect(newNote, &QAction::triggered, this, [this]() { emit newFileTriggered(0); });
    QObject::connect(newDoc, &QAction::triggered, this, [this]() { emit newFileTriggered(1); });
    QObject::connect(newSheet, &QAction::triggered, this, [this]() { emit newFileTriggered(2); });
    QObject::connect(importAction, &QAction::triggered, this, &MenuManagerBrick::importTriggered);
    QObject::connect(exportAction, &QAction::triggered, this, &MenuManagerBrick::exportTriggered);
    QObject::connect(saveAsAction, &QAction::triggered, this, [this]() { emit saveAsTriggered(); });
    QObject::connect(exitAction, &QAction::triggered, this, &MenuManagerBrick::exitTriggered);

    QObject::connect(insertRowAbove, &QAction::triggered, this, &MenuManagerBrick::insertRowAboveTriggered);
    QObject::connect(insertRowBelow, &QAction::triggered, this, &MenuManagerBrick::insertRowBelowTriggered);
    QObject::connect(insertColumnBefore, &QAction::triggered, this, &MenuManagerBrick::insertColumnBeforeTriggered);
    QObject::connect(insertColumnAfter, &QAction::triggered, this, &MenuManagerBrick::insertColumnAfterTriggered);
    QObject::connect(deleteRow, &QAction::triggered, this, &MenuManagerBrick::deleteRowTriggered);
    QObject::connect(deleteColumn, &QAction::triggered, this, &MenuManagerBrick::deleteColumnTriggered);
    QObject::connect(deleteTable, &QAction::triggered, this, &MenuManagerBrick::deleteTableTriggered);
    QObject::connect(mergeCells, &QAction::triggered, this, &MenuManagerBrick::mergeCellsTriggered);
    QObject::connect(splitCells, &QAction::triggered, this, &MenuManagerBrick::splitCellsTriggered);
    QObject::connect(alignTableLeft, &QAction::triggered, this, &MenuManagerBrick::alignTableLeftTriggered);
    QObject::connect(alignTableCenter, &QAction::triggered, this, &MenuManagerBrick::alignTableCenterTriggered);
    QObject::connect(alignTableRight, &QAction::triggered, this, &MenuManagerBrick::alignTableRightTriggered);

    qDebug() << "Menus set up. Format menu actions:" << formatMenu->actions().count();
}

QMenuBar* MenuManagerBrick::getMenuBar() const {
    return menuBar;
}

MenuManagerBrick::~MenuManagerBrick() {}
