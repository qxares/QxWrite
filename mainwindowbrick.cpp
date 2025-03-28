#include "mainwindowbrick.h"
#include "toolbarbrick.h"
#include "menumanagerbrick.h"
#include "newfilebrick.h"
#include "openfilebrick.h"
#include "savemanagerbrick.h"
#include "boldbrick.h"
#include "italicbrick.h"
#include "fontbrick.h"
#include "colorbrick.h"
#include "insertbrick.h"
#include "alignbrick.h"
#include "listbrick.h"
#include "tablebrick.h"
#include "documentwindow.h"
#include "documenthandlerbrick.h"
#include <QDebug>
#include <QMenu>
#include <QMdiSubWindow>

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "MainWindowBrick starting...";

    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

    documentHandler = new DocumentHandlerBrick(this);

    toolBarBrick = new ToolBarBrick(this);
    addToolBar(toolBarBrick->getToolBar());

    menuManagerBrick = new MenuManagerBrick(this);
    setMenuBar(menuManagerBrick->getMenuBar());

    menuManagerBrick->setupMenus(
        toolBarBrick->getAction("open"), toolBarBrick->getAction("save"),
        toolBarBrick->getAction("bold"), toolBarBrick->getAction("italic"), toolBarBrick->getAction("font"),
        toolBarBrick->getAction("color"), toolBarBrick->getAction("image"), toolBarBrick->getAction("alignLeft"),
        toolBarBrick->getAction("alignCenter"), toolBarBrick->getAction("alignRight"),
        nullptr, nullptr, nullptr
    );

    connect(menuManagerBrick, &MenuManagerBrick::newFileTriggered, this, [this](int type) {
        qDebug() << "MainWindowBrick: New file triggered with type" << type;
        QTextEdit *textEdit = documentHandler->newDocument(static_cast<NewFileBrick::DocType>(type));
        if (!textEdit) {
            qDebug() << "MainWindowBrick: Failed to create new document!";
            return;
        }

        // Fresh bricks per document
        auto *newFileBrick = new NewFileBrick(textEdit, this);
        auto *openFileBrick = new OpenFileBrick(textEdit, this);
        auto *saveManagerBrick = new SaveManagerBrick(textEdit, this);
        auto *boldBrick = new BoldBrick(textEdit, this);
        auto *italicBrick = new ItalicBrick(textEdit, this);
        auto *fontBrick = new FontBrick(textEdit, this);
        auto *colorBrick = new ColorBrick(textEdit, this);
        auto *insertBrick = new InsertBrick(textEdit, this);
        auto *alignBrick = new AlignBrick(textEdit, this);
        auto *listBrick = new ListBrick(textEdit, this);
        auto *tableBrick = new TableBrick(textEdit, this);

        // Menu connections
        connect(menuManagerBrick, &MenuManagerBrick::saveAsTriggered, this, [saveManagerBrick]() {
            saveManagerBrick->triggerSave();
        });
        connect(menuManagerBrick, &MenuManagerBrick::numberingTriggered, this, [listBrick]() {
            listBrick->toggleNumbering();
        });
        connect(menuManagerBrick, &MenuManagerBrick::bulletsTriggered, this, [listBrick]() {
            listBrick->toggleBullets();
        });
        connect(menuManagerBrick, &MenuManagerBrick::insertTableTriggered, this, [tableBrick]() {
            tableBrick->insertTable();
        });
        connect(menuManagerBrick, &MenuManagerBrick::insertRowBeforeTriggered, this, [tableBrick]() {
            tableBrick->insertRowBefore();
        });
        connect(menuManagerBrick, &MenuManagerBrick::insertRowAfterTriggered, this, [tableBrick]() {
            tableBrick->insertRowAfter();
        });
        connect(menuManagerBrick, &MenuManagerBrick::insertRowAboveTriggered, this, [tableBrick]() {
            tableBrick->insertRowAbove();
        });
        connect(menuManagerBrick, &MenuManagerBrick::insertRowBelowTriggered, this, [tableBrick]() {
            tableBrick->insertRowBelow();
        });
        connect(menuManagerBrick, &MenuManagerBrick::insertColumnBeforeTriggered, this, [tableBrick]() {
            tableBrick->insertColumnBefore();
        });
        connect(menuManagerBrick, &MenuManagerBrick::insertColumnAfterTriggered, this, [tableBrick]() {
            tableBrick->insertColumnAfter();
        });
        connect(menuManagerBrick, &MenuManagerBrick::insertColumnAboveTriggered, this, [tableBrick]() {
            tableBrick->insertColumnAbove();
        });
        connect(menuManagerBrick, &MenuManagerBrick::insertColumnBelowTriggered, this, [tableBrick]() {
            tableBrick->insertColumnBelow();
        });
        connect(menuManagerBrick, &MenuManagerBrick::deleteRowTriggered, this, [tableBrick]() {
            tableBrick->deleteRow();
        });
        connect(menuManagerBrick, &MenuManagerBrick::deleteColumnTriggered, this, [tableBrick]() {
            tableBrick->deleteColumn();
        });
        connect(menuManagerBrick, &MenuManagerBrick::mergeCellsTriggered, this, [tableBrick]() {
            tableBrick->mergeCells();
        });
        connect(menuManagerBrick, &MenuManagerBrick::deleteTableTriggered, this, [tableBrick]() {
            tableBrick->deleteTable();
        });
        connect(menuManagerBrick, &MenuManagerBrick::alignTableLeftTriggered, this, [tableBrick]() {
            qDebug() << "MainWindowBrick: alignTableLeftTriggered fired";
            tableBrick->alignTableLeft();
        });
        connect(menuManagerBrick, &MenuManagerBrick::alignTableCenterTriggered, this, [tableBrick]() {
            qDebug() << "MainWindowBrick: alignTableCenterTriggered fired";
            tableBrick->alignTableCenter();
        });
        connect(menuManagerBrick, &MenuManagerBrick::alignTableRightTriggered, this, [tableBrick]() {
            qDebug() << "MainWindowBrick: alignTableRightTriggered fired";
            tableBrick->alignTableRight();
        });

        // Toolbar connections
        connect(toolBarBrick->getAction("open"), &QAction::triggered, this, &MainWindowBrick::handleOpenFile);
        connect(toolBarBrick->getAction("save"), &QAction::triggered, this, [saveManagerBrick]() {
            saveManagerBrick->triggerSave();
        });
        connect(toolBarBrick->getAction("bold"), &QAction::triggered, this, [boldBrick]() {
            boldBrick->applyBold();
        });
        connect(toolBarBrick->getAction("italic"), &QAction::triggered, this, [italicBrick]() {
            italicBrick->applyItalic();
        });
        connect(toolBarBrick->getAction("font"), &QAction::triggered, this, [fontBrick]() {
            fontBrick->changeFont();
        });
        connect(toolBarBrick->getAction("color"), &QAction::triggered, this, [colorBrick]() {
            colorBrick->changeColor();
        });
        connect(toolBarBrick->getAction("image"), &QAction::triggered, this, [insertBrick]() {
            insertBrick->insertImage();
        });
        connect(toolBarBrick->getAction("alignLeft"), &QAction::triggered, this, [alignBrick]() {
            qDebug() << "MainWindowBrick: Toolbar alignLeft triggered";
            alignBrick->align(Qt::AlignLeft);
        });
        connect(toolBarBrick->getAction("alignCenter"), &QAction::triggered, this, [alignBrick]() {
            qDebug() << "MainWindowBrick: Toolbar alignCenter triggered";
            alignBrick->align(Qt::AlignCenter);
        });
        connect(toolBarBrick->getAction("alignRight"), &QAction::triggered, this, [alignBrick]() {
            qDebug() << "MainWindowBrick: Toolbar alignRight triggered";
            alignBrick->align(Qt::AlignRight);
        });
    });

    resize(800, 600);
    qDebug() << "MainWindowBrick ready.";
}

void MainWindowBrick::handleOpenFile() {
    documentHandler->openDocument(new OpenFileBrick(nullptr, this)); // Fresh instance, updated later if needed
}

MainWindowBrick::~MainWindowBrick() {}
