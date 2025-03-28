#include "menumanagerbrick.h"
#include <QMenuBar>
#include <QMenu>
#include <QDebug>

MenuManagerBrick::MenuManagerBrick(QWidget *parent) : QObject(parent) {
    menuBar = new QMenuBar(parent);
    fileMenu = new QMenu("File", menuBar);
    editMenu = new QMenu("Edit", menuBar);
    formatMenu = new QMenu("Format", menuBar);
    tableMenu = new QMenu("Table", menuBar);
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);
    menuBar->addMenu(formatMenu);
    menuBar->addMenu(tableMenu);
    qDebug() << "MenuManagerBrick initialized, menuBar:" << menuBar;
}

void MenuManagerBrick::setupMenus(QAction *openAction, QAction *saveAction,
                                  QAction *boldAction, QAction *italicAction, QAction *fontAction,
                                  QAction *colorAction, QAction *imageAction, QAction *alignLeftAction,
                                  QAction *alignCenterAction, QAction *alignRightAction,
                                  QAction *numberingAction, QAction *bulletsAction,
                                  QAction *tableAction) {
    QAction *newActionMenu = fileMenu->addAction("New");
    QMenu *newMenu = new QMenu();
    QAction *newNote = newMenu->addAction("QxNote");
    QAction *newDoc = newMenu->addAction("QxDocument");
    QAction *newSheet = newMenu->addAction("QxSheet");
    newActionMenu->setMenu(newMenu);

    QAction *saveAsAction = fileMenu->addAction("Save As");
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
    QAction *insertTable = tableMenu->addAction("Insert Table");
    QMenu *insertMenu = new QMenu("Insert", tableMenu);
    QAction *insertRowMenu = insertMenu->addAction("Add Row");
    QAction *insertColumnMenu = insertMenu->addAction("Add Column");
    QMenu *deleteMenu = new QMenu("Delete", tableMenu);
    QAction *mergeCells = tableMenu->addAction("Merge Cells");

    QMenu *rowMenu = new QMenu("Row", insertMenu);
    QAction *insertRowBefore = rowMenu->addAction("Insert Before");
    QAction *insertRowAfter = rowMenu->addAction("Insert After");
    QAction *insertRowAbove = rowMenu->addAction("Insert Above");
    QAction *insertRowBelow = rowMenu->addAction("Insert Below");
    insertRowMenu->setMenu(rowMenu);

    QMenu *columnMenu = new QMenu("Column", insertMenu);
    QAction *insertColumnBefore = columnMenu->addAction("Insert Before");
    QAction *insertColumnAfter = columnMenu->addAction("Insert After");
    QAction *insertColumnAbove = columnMenu->addAction("Insert Above");
    QAction *insertColumnBelow = columnMenu->addAction("Insert Below");
    insertColumnMenu->setMenu(columnMenu);

    QAction *deleteRow = deleteMenu->addAction("Selected Row");
    QAction *deleteColumn = deleteMenu->addAction("Selected Column");
    QAction *deleteTable = deleteMenu->addAction("Table"); // New: Delete Table option

    tableMenu->addMenu(insertMenu);
    tableMenu->addMenu(deleteMenu);

    // New: Table alignment options
    QMenu *alignMenu = new QMenu("Align Table", tableMenu);
    QAction *alignTableLeft = alignMenu->addAction("Left");
    QAction *alignTableCenter = alignMenu->addAction("Center");
    QAction *alignTableRight = alignMenu->addAction("Right");
    tableMenu->addMenu(alignMenu);

    QObject::connect(insertTable, &QAction::triggered, this, &MenuManagerBrick::insertTableTriggered);
    QObject::connect(insertRowBefore, &QAction::triggered, this, &MenuManagerBrick::insertRowBeforeTriggered);
    QObject::connect(insertRowAfter, &QAction::triggered, this, &MenuManagerBrick::insertRowAfterTriggered);
    QObject::connect(insertRowAbove, &QAction::triggered, this, &MenuManagerBrick::insertRowAboveTriggered);
    QObject::connect(insertRowBelow, &QAction::triggered, this, &MenuManagerBrick::insertRowBelowTriggered);
    QObject::connect(insertColumnBefore, &QAction::triggered, this, &MenuManagerBrick::insertColumnBeforeTriggered);
    QObject::connect(insertColumnAfter, &QAction::triggered, this, &MenuManagerBrick::insertColumnAfterTriggered);
    QObject::connect(insertColumnAbove, &QAction::triggered, this, &MenuManagerBrick::insertColumnAboveTriggered);
    QObject::connect(insertColumnBelow, &QAction::triggered, this, &MenuManagerBrick::insertColumnBelowTriggered);
    QObject::connect(deleteRow, &QAction::triggered, this, &MenuManagerBrick::deleteRowTriggered);
    QObject::connect(deleteColumn, &QAction::triggered, this, &MenuManagerBrick::deleteColumnTriggered);
    QObject::connect(deleteTable, &QAction::triggered, this, &MenuManagerBrick::deleteTableTriggered); // New signal
    QObject::connect(mergeCells, &QAction::triggered, this, &MenuManagerBrick::mergeCellsTriggered);
    QObject::connect(alignTableLeft, &QAction::triggered, this, &MenuManagerBrick::alignTableLeftTriggered);   // New signal
    QObject::connect(alignTableCenter, &QAction::triggered, this, &MenuManagerBrick::alignTableCenterTriggered); // New signal
    QObject::connect(alignTableRight, &QAction::triggered, this, &MenuManagerBrick::alignTableRightTriggered);  // New signal

    QAction *menuNumbering = new QAction("Numbering", this);
    menuNumbering->setToolTip("Toggle numbered list");
    formatMenu->addAction(menuNumbering);
    QObject::connect(menuNumbering, &QAction::triggered, this, &MenuManagerBrick::numberingTriggered);

    QAction *menuBullets = new QAction("Bullets", this);
    menuBullets->setToolTip("Toggle bulleted list");
    formatMenu->addAction(menuBullets);
    QObject::connect(menuBullets, &QAction::triggered, this, &MenuManagerBrick::bulletsTriggered);

    if (imageAction) {
        QAction *menuImage = new QAction("Image", this);
        menuImage->setToolTip(imageAction->toolTip());
        editMenu->addAction(menuImage);
        QObject::connect(menuImage, &QAction::triggered, imageAction, &QAction::trigger);
    }
    formatMenu->addSeparator();
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

    QObject::connect(newNote, &QAction::triggered, this, 
