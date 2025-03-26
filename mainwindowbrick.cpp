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
#include "documentwindow.h"
#include <QDebug>
#include <QMenu>

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "MainWindowBrick starting...";

    documentWindow = new DocumentWindow(this);
    setCentralWidget(documentWindow);

    toolBarBrick = new ToolBarBrick(this);
    addToolBar(toolBarBrick->getToolBar());

    menuManagerBrick = new MenuManagerBrick(this);
    setMenuBar(menuManagerBrick->getMenuBar());

    newFileBrick = new NewFileBrick(documentWindow->getTextEdit(), this);
    openFileBrick = new OpenFileBrick(documentWindow->getTextEdit(), this);
    saveManagerBrick = new SaveManagerBrick(documentWindow->getTextEdit(), this);
    boldBrick = new BoldBrick(documentWindow->getTextEdit(), this);
    italicBrick = new ItalicBrick(documentWindow->getTextEdit(), this);
    fontBrick = new FontBrick(documentWindow->getTextEdit(), this);
    colorBrick = new ColorBrick(documentWindow->getTextEdit(), this);
    insertBrick = new InsertBrick(documentWindow->getTextEdit(), this);
    alignBrick = new AlignBrick(documentWindow->getTextEdit(), this);

    // Nest "New" submenu under "File"
    QMenu *fileMenu = menuManagerBrick->getMenuBar()->addMenu("File");
    QMenu *newMenu = fileMenu->addMenu("New");
    QAction *newNote = newMenu->addAction("QxNote");
    QAction *newDoc = newMenu->addAction("QxDocument");
    QAction *newSheet = newMenu->addAction("QxSheet");

    menuManagerBrick->setupMenus(
        nullptr, toolBarBrick->getAction("open"), toolBarBrick->getAction("save"),
        toolBarBrick->getAction("bold"), toolBarBrick->getAction("italic"), toolBarBrick->getAction("font"),
        toolBarBrick->getAction("color"), toolBarBrick->getAction("image"), toolBarBrick->getAction("alignLeft"),
        toolBarBrick->getAction("alignCenter"), toolBarBrick->getAction("alignRight")
    );

    connect(newNote, &QAction::triggered, this, [this]() { documentWindow->newFile(NewFileBrick::Note); });
    connect(newDoc, &QAction::triggered, this, [this]() { documentWindow->newFile(NewFileBrick::Document); });
    connect(newSheet, &QAction::triggered, this, [this]() { documentWindow->newFile(NewFileBrick::Sheet); });
    connect(toolBarBrick->getAction("new"), &QAction::triggered, this, [this]() { documentWindow->newFile(NewFileBrick::Note); });  // Toolbar defaults to Note
    connect(toolBarBrick->getAction("open"), &QAction::triggered, this, [this]() {
        qDebug() << "MainWindowBrick: Triggering Open in current DocumentWindow (Toolbar)";
        openFileBrick->openFile();
    });
    connect(toolBarBrick->getAction("save"), &QAction::triggered, saveManagerBrick, &SaveManagerBrick::triggerSave);
    connect(toolBarBrick->getAction("bold"), &QAction::triggered, boldBrick, &BoldBrick::applyBold);
    connect(toolBarBrick->getAction("italic"), &QAction::triggered, italicBrick, &ItalicBrick::applyItalic);
    connect(toolBarBrick->getAction("font"), &QAction::triggered, fontBrick, &FontBrick::changeFont);
    connect(toolBarBrick->getAction("color"), &QAction::triggered, colorBrick, &ColorBrick::changeColor);
    connect(toolBarBrick->getAction("image"), &QAction::triggered, insertBrick, &InsertBrick::insertImage);
    connect(toolBarBrick->getAction("alignLeft"), &QAction::triggered, this, [this]() { alignBrick->align(Qt::AlignLeft); });
    connect(toolBarBrick->getAction("alignCenter"), &QAction::triggered, this, [this]() { alignBrick->align(Qt::AlignCenter); });
    connect(toolBarBrick->getAction("alignRight"), &QAction::triggered, this, [this]() { alignBrick->align(Qt::AlignRight); });

    resize(800, 600);  // Locked in at 800x600—adjust if needed

    qDebug() << "MainWindowBrick ready.";
}

MainWindowBrick::~MainWindowBrick() {}
