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

    newFileBrick = new NewFileBrick(nullptr, this);
    openFileBrick = new OpenFileBrick(nullptr, this);
    saveManagerBrick = new SaveManagerBrick(nullptr, this);
    boldBrick = new BoldBrick(nullptr, this);
    italicBrick = new ItalicBrick(nullptr, this);
    fontBrick = new FontBrick(nullptr, this);
    colorBrick = new ColorBrick(nullptr, this);
    insertBrick = new InsertBrick(nullptr, this);
    alignBrick = new AlignBrick(nullptr, this);
    listBrick = new ListBrick(nullptr, this);
    tableBrick = new TableBrick(nullptr, this);

    menuManagerBrick->setupMenus(
        toolBarBrick->getAction("open"), toolBarBrick->getAction("save"),
        toolBarBrick->getAction("bold"), toolBarBrick->getAction("italic"), toolBarBrick->getAction("font"),
        toolBarBrick->getAction("color"), toolBarBrick->getAction("image"), toolBarBrick->getAction("alignLeft"),
        toolBarBrick->getAction("alignCenter"), toolBarBrick->getAction("alignRight"),
        nullptr, nullptr, toolBarBrick->getAction("table") // Will be null, handled by menu
    );

    connect(menuManagerBrick, &MenuManagerBrick::newFileTriggered, this, [this](int type) {
        documentHandler->newDocument(static_cast<NewFileBrick::DocType>(type));
    });
    connect(menuManagerBrick, &MenuManagerBrick::saveAsTriggered, this, [this]() {
        if (auto *subWindow = mdiArea->activeSubWindow()) {
            if (auto *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget())) {
                saveManagerBrick->setTextEdit(docWindow->getTextEdit());
                saveManagerBrick->triggerSave();
            } else {
                qDebug() << "MainWindowBrick: No active document window for Save As";
            }
        } else {
            qDebug() << "MainWindowBrick: No active subwindow for Save As";
        }
    });
    connect(menuManagerBrick, &MenuManagerBrick::numberingTriggered, this, [this]() {
        if (auto *subWindow = mdiArea->activeSubWindow()) {
            if (auto *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget())) {
                listBrick->setTextEdit(docWindow->getTextEdit());
                listBrick->toggleNumbering();
            }
        }
    });
    connect(menuManagerBrick, &MenuManagerBrick::bulletsTriggered, this, [this]() {
        if (auto *subWindow = mdiArea->activeSubWindow()) {
            if (auto *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget())) {
                listBrick->setTextEdit(docWindow->getTextEdit());
                listBrick->toggleBullets();
            }
        }
    });
    connect(menuManagerBrick, &MenuManagerBrick::tableTriggered, this, [this]() {
        if (auto *subWindow = mdiArea->activeSubWindow()) {
            if (auto *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget())) {
                tableBrick->setTextEdit(docWindow->getTextEdit());
                tableBrick->insertTable();
                qDebug() << "Table insertion triggered from menu";
            } else {
                qDebug() << "No active document window for table insertion";
            }
        } else {
            qDebug() << "No active subwindow for table insertion";
        }
    });
    connect(toolBarBrick->getAction("open"), &QAction::triggered, this, &MainWindowBrick::handleOpenFile);
    connect(toolBarBrick->getAction("save"), &QAction::triggered, this, [this]() {
        if (auto *subWindow = mdiArea->activeSubWindow()) {
            if (auto *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget())) {
                saveManagerBrick->setTextEdit(docWindow->getTextEdit());
                saveManagerBrick->triggerSave();
            } else {
                qDebug() << "MainWindowBrick: No active document window for Save";
            }
        } else {
            qDebug() << "MainWindowBrick: No active subwindow for Save";
        }
    });
    connect(toolBarBrick->getAction("bold"), &QAction::triggered, this, [this]() {
        if (auto *subWindow = mdiArea->activeSubWindow()) {
            if (auto *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget())) {
                boldBrick->setTextEdit(docWindow->getTextEdit());
                boldBrick->applyBold();
            }
        }
    });
    connect(toolBarBrick->getAction("italic"), &QAction::triggered, this, [this]() {
        if (auto *subWindow = mdiArea->activeSubWindow()) {
            if (auto *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget())) {
                italicBrick->setTextEdit(docWindow->getTextEdit());
                italicBrick->applyItalic();
            }
        }
    });
    connect(toolBarBrick->getAction("font"), &QAction::triggered, this, [this]() {
        if (auto *subWindow = mdiArea->activeSubWindow()) {
            if (auto *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget())) {
                fontBrick->setTextEdit(docWindow->getTextEdit());
                fontBrick->changeFont();
            }
        }
    });
    connect(toolBarBrick->getAction("color"), &QAction::triggered, this, [this]() {
        if (auto *subWindow = mdiArea->activeSubWindow()) {
            if (auto *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget())) {
                colorBrick->setTextEdit(docWindow->getTextEdit());
                colorBrick->changeColor();
            }
        }
    });
    connect(toolBarBrick->getAction("image"), &QAction::triggered, this, [this]() {
        if (auto *subWindow = mdiArea->activeSubWindow()) {
            if (auto *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget())) {
                insertBrick->setTextEdit(docWindow->getTextEdit());
                insertBrick->insertImage();
            }
        }
    });
    connect(toolBarBrick->getAction("alignLeft"), &QAction::triggered, this, [this]() {
        if (auto *subWindow = mdiArea->activeSubWindow()) {
            if (auto *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget())) {
                alignBrick->setTextEdit(docWindow->getTextEdit());
                alignBrick->align(Qt::AlignLeft);
            }
        }
    });
    connect(toolBarBrick->getAction("alignCenter"), &QAction::triggered, this, [this]() {
        if (auto *subWindow = mdiArea->activeSubWindow()) {
            if (auto *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget())) {
                alignBrick->setTextEdit(docWindow->getTextEdit());
                alignBrick->align(Qt::AlignCenter);
            }
        }
    });
    connect(toolBarBrick->getAction("alignRight"), &QAction::triggered, this, [this]() {
        if (auto *subWindow = mdiArea->activeSubWindow()) {
            if (auto *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget())) {
                alignBrick->setTextEdit(docWindow->getTextEdit());
                alignBrick->align(Qt::AlignRight);
            }
        }
    });

    resize(800, 600);

    qDebug() << "MainWindowBrick ready.";
}

void MainWindowBrick::handleOpenFile() {
    documentHandler->openDocument(openFileBrick);
}

MainWindowBrick::~MainWindowBrick() {}
