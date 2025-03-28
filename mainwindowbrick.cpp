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

    QAction *openAction = toolBarBrick->addAction("open", "Open", ":/icons/icons/open.svg");
    QAction *saveAction = toolBarBrick->addAction("save", "Save", ":/icons/icons/save.svg");
    QAction *boldAction = toolBarBrick->addAction("bold", "Bold", ":/icons/icons/bold.svg");
    QAction *italicAction = toolBarBrick->addAction("italic", "Italic", ":/icons/icons/italic.svg");
    QAction *fontAction = toolBarBrick->addAction("font", "Font", ":/icons/icons/font.svg");
    QAction *colorAction = toolBarBrick->addAction("color", "Color", ":/icons/icons/color.svg");
    QAction *imageAction = toolBarBrick->addAction("image", "Insert Image", ":/icons/icons/image.svg");
    QAction *alignLeftAction = toolBarBrick->addAction("alignLeft", "Align Left", ":/icons/icons/align-left.svg");
    QAction *alignCenterAction = toolBarBrick->addAction("alignCenter", "Align Center", ":/icons/icons/align-center.svg");
    QAction *alignRightAction = toolBarBrick->addAction("alignRight", "Align Right", ":/icons/icons/align-right.svg");
    QAction *tableAction = toolBarBrick->addAction("table", "Insert Table", ":/icons/icons/table.svg");

    menuManagerBrick->setupMenus(openAction, saveAction, boldAction, italicAction, fontAction,
                                 colorAction, imageAction, alignLeftAction, alignCenterAction,
                                 alignRightAction, nullptr, nullptr, tableAction);

    connect(menuManagerBrick, &MenuManagerBrick::newFileTriggered, this, [this](int type) {
        QTextEdit *textEdit = documentHandler->newDocument(static_cast<NewFileBrick::DocType>(type));
        if (!textEdit) return;

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
        auto *resizeBrick = new ResizeBrick(textEdit, this);
        resizeBrick->enableResize();

        connect(openAction, &QAction::triggered, openFileBrick, &OpenFileBrick::openFile);
        connect(saveAction, &QAction::triggered, saveManagerBrick, &SaveManagerBrick::triggerSave);
        connect(boldAction, &QAction::triggered, boldBrick, &BoldBrick::toggleBold);
        connect(italicAction, &QAction::triggered, italicBrick, &ItalicBrick::toggleItalic);
        connect(fontAction, &QAction::triggered, fontBrick, &FontBrick::selectFont);
        connect(colorAction, &QAction::triggered, colorBrick, &ColorBrick::selectColor);
        connect(imageAction, &QAction::triggered, insertBrick, &InsertBrick::insertImage);
        connect(alignLeftAction, &QAction::triggered, alignBrick, &AlignBrick::alignLeft);
        connect(alignCenterAction, &QAction::triggered, alignBrick, &AlignBrick::alignCenter);
        connect(alignRightAction, &QAction::triggered, alignBrick, &AlignBrick::alignRight);
        connect(tableAction, &QAction::triggered, tableBrick, &TableBrick::insertTable);

        connect(menuManagerBrick, &MenuManagerBrick::saveAsTriggered, saveManagerBrick, &SaveManagerBrick::triggerSave);
        connect(menuManagerBrick, &MenuManagerBrick::alignTableLeftTriggered, tableBrick, &TableBrick::alignTableLeft);
        connect(menuManagerBrick, &MenuManagerBrick::alignTableCenterTriggered, tableBrick, &TableBrick::alignTableCenter);
        connect(menuManagerBrick, &MenuManagerBrick::alignTableRightTriggered, tableBrick, &TableBrick::alignTableRight);
        connect(menuManagerBrick, &MenuManagerBrick::moveTriggered, resizeBrick, &ResizeBrick::moveObject);

        QMenu *tableMenu = menuManagerBrick->getMenuBar()->findChild<QMenu*>("tableMenu");
        if (tableMenu) {
            tableMenu->addAction("Move", [resizeBrick]() { resizeBrick->moveObject(); });
        }
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
