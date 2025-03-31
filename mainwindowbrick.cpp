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
#include "tablehandlerbrick.h"
#include "documenthandlerbrick.h"
#include "resizebrick.h"
#include <QMdiArea>
#include <QMenu>
#include <QDebug>

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

    documentHandler = new DocumentHandlerBrick(this);
    toolBarBrick = new ToolBarBrick(this);
    menuManagerBrick = new MenuManagerBrick(this);
    activeTableHandler = nullptr;

    addToolBar(toolBarBrick->getToolBar());
    setMenuBar(menuManagerBrick->getMenuBar());

    resize(800, 600);

    QAction *openAction = toolBarBrick->getAction("open");
    QAction *saveAction = toolBarBrick->getAction("save");
    QAction *boldAction = toolBarBrick->getAction("bold");
    QAction *italicAction = toolBarBrick->getAction("italic");
    QAction *fontAction = toolBarBrick->getAction("font");
    QAction *colorAction = toolBarBrick->getAction("color");
    QAction *imageAction = toolBarBrick->getAction("image");
    QAction *alignLeftAction = toolBarBrick->getAction("alignLeft");
    QAction *alignCenterAction = toolBarBrick->getAction("alignCenter");
    QAction *alignRightAction = toolBarBrick->getAction("alignRight");
    QAction *tableAction = new QAction("Insert Table", this);

    menuManagerBrick->setupMenus(openAction, saveAction, boldAction, italicAction, fontAction,
                                 colorAction, imageAction, alignLeftAction, alignCenterAction,
                                 alignRightAction, nullptr, nullptr, tableAction);

    connect(menuManagerBrick, &MenuManagerBrick::newFileTriggered, this, [this, openAction, saveAction, boldAction, italicAction, fontAction, colorAction, imageAction, alignLeftAction, alignCenterAction, alignRightAction, tableAction](int type) {
        QTextEdit *textEdit = documentHandler->newDocument(static_cast<NewFileBrick::DocType>(type));
        if (!textEdit) return;

        auto *openFileBrick = new OpenFileBrick(textEdit, this);
        auto *saveManagerBrick = new SaveManagerBrick(textEdit, this);
        auto *boldBrick = new BoldBrick(textEdit, this);
        auto *italicBrick = new ItalicBrick(textEdit, this);
        auto *fontBrick = new FontBrick(textEdit, this);
        auto *colorBrick = new ColorBrick(textEdit, this);
        auto *insertBrick = new InsertBrick(textEdit, this);
        auto *alignBrick = new AlignBrick(textEdit, this);
        auto *tableBrick = new TableBrick(textEdit, this);
        auto *tableHandlerBrick = new TableHandlerBrick(textEdit, this);
        auto *resizeBrick = new ResizeBrick(textEdit, this);
        resizeBrick->enableResize();

        activeTableHandler = tableHandlerBrick;

        connect(openAction, &QAction::triggered, openFileBrick, &OpenFileBrick::openFile);
        connect(saveAction, &QAction::triggered, saveManagerBrick, &SaveManagerBrick::triggerSave);
        connect(boldAction, &QAction::triggered, boldBrick, &BoldBrick::applyBold);
        connect(italicAction, &QAction::triggered, italicBrick, &ItalicBrick::applyItalic);
        connect(fontAction, &QAction::triggered, fontBrick, &FontBrick::changeFont);
        connect(colorAction, &QAction::triggered, colorBrick, &ColorBrick::changeColor);
        connect(imageAction, &QAction::triggered, insertBrick, &InsertBrick::insertImage);
        connect(alignLeftAction, &QAction::triggered, alignBrick, [alignBrick]() { alignBrick->align(Qt::AlignLeft); });
        connect(alignCenterAction, &QAction::triggered, alignBrick, [alignBrick]() { alignBrick->align(Qt::AlignCenter); });
        connect(alignRightAction, &QAction::triggered, alignBrick, [alignBrick]() { alignBrick->align(Qt::AlignRight); });
        connect(tableAction, &QAction::triggered, tableBrick, &TableBrick::insertTable);

        connect(menuManagerBrick, &MenuManagerBrick::saveAsTriggered, saveManagerBrick, &SaveManagerBrick::triggerSave);
        connect(menuManagerBrick, &MenuManagerBrick::insertRowBeforeTriggered, tableBrick, &TableBrick::insertRowBefore);
        connect(menuManagerBrick, &MenuManagerBrick::insertRowAfterTriggered, tableBrick, &TableBrick::insertRowAfter);
        connect(menuManagerBrick, &MenuManagerBrick::insertRowAboveTriggered, tableBrick, &TableBrick::insertRowAbove);
        connect(menuManagerBrick, &MenuManagerBrick::insertRowBelowTriggered, tableBrick, &TableBrick::insertRowBelow);
        connect(menuManagerBrick, &MenuManagerBrick::insertColumnBeforeTriggered, tableBrick, &TableBrick::insertColumnBefore);
        connect(menuManagerBrick, &MenuManagerBrick::insertColumnAfterTriggered, tableBrick, &TableBrick::insertColumnAfter);
        connect(menuManagerBrick, &MenuManagerBrick::insertColumnAboveTriggered, tableBrick, &TableBrick::insertColumnAbove);
        connect(menuManagerBrick, &MenuManagerBrick::insertColumnBelowTriggered, tableBrick, &TableBrick::insertColumnBelow);
        connect(menuManagerBrick, &MenuManagerBrick::deleteRowTriggered, tableBrick, &TableBrick::deleteRow);
        connect(menuManagerBrick, &MenuManagerBrick::deleteColumnTriggered, tableBrick, &TableBrick::deleteColumn);
        connect(menuManagerBrick, &MenuManagerBrick::mergeCellsTriggered, tableBrick, &TableBrick::mergeCells);
        connect(menuManagerBrick, &MenuManagerBrick::deleteTableTriggered, tableHandlerBrick, &TableHandlerBrick::deleteTable);
        connect(menuManagerBrick, &MenuManagerBrick::alignTableLeftTriggered, tableHandlerBrick, &TableHandlerBrick::alignTableLeft);
        connect(menuManagerBrick, &MenuManagerBrick::alignTableCenterTriggered, tableHandlerBrick, &TableHandlerBrick::alignTableCenter);
        connect(menuManagerBrick, &MenuManagerBrick::alignTableRightTriggered, tableHandlerBrick, &TableHandlerBrick::alignTableRight);
        connect(menuManagerBrick, &MenuManagerBrick::moveTriggered, resizeBrick, &ResizeBrick::moveObject);

        QMenu *tableMenu = menuManagerBrick->getMenuBar()->findChild<QMenu*>("Table");
        if (tableMenu) {
            tableMenu->addAction("Move", [resizeBrick]() { resizeBrick->moveObject(); });
        }

        connect(mdiArea, &QMdiArea::subWindowActivated, this, [this, textEdit, tableHandlerBrick]() {
            if (mdiArea->activeSubWindow() && mdiArea->activeSubWindow()->widget()) {
                QTextEdit *activeEdit = qobject_cast<DocumentWindow*>(mdiArea->activeSubWindow()->widget())->getTextEdit();
                if (activeEdit == textEdit) {
                    activeTableHandler = tableHandlerBrick;
                }
            }
        });
    });

    connect(openAction, &QAction::triggered, this, &MainWindowBrick::handleOpenFile);

    qDebug() << "MainWindowBrick ready.";
}

MainWindowBrick::~MainWindowBrick() {
    delete toolBarBrick;
    delete menuManagerBrick;
    delete documentHandler;
}

void MainWindowBrick::handleOpenFile() {
    documentHandler->openDocument(new OpenFileBrick(nullptr, this));
}
