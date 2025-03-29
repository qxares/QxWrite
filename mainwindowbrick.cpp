#include "mainwindowbrick.h"
#include <QTextEdit>
#include <QDebug>
#include <QToolBar>
#include "boldbrick.h" // Covers BoldBrick logic (function, handler, and GUI for now)
#include "italicbrick.h" // Covers ItalicBrick logic (function, handler, and GUI for now)
#include "savefunctionbrick.h"
#include "savehandlerbrick.h"
#include "saveguibrick.h"
#include "savemanagerbrick.h"
#include "placeholderbrick.h"

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "MainWindowBrick starting...";
    edit = new QTextEdit(this);
    setCentralWidget(edit);
    resize(800, 600);

    // Bold Action
    BoldBrick *boldFunction = new BoldBrick(edit, this);
    BoldBrick *boldHandler = new BoldBrick(edit, this);
    BoldBrick *boldGui = new BoldBrick(edit, this);

    // Italic Action
    ItalicBrick *italicFunction = new ItalicBrick(edit, this);
    ItalicBrick *italicHandler = new ItalicBrick(edit, this);
    ItalicBrick *italicGui = new ItalicBrick(edit, this);

    // Save Action
    SaveFunctionBrick *saveFunction = new SaveFunctionBrick(edit, this);
    SaveGUIBrick *saveGui = new SaveGUIBrick(this); // Fixed typo: SaveGuiBrick -> SaveGUIBrick
    SaveHandlerBrick *saveHandler = new SaveHandlerBrick(saveFunction, saveGui, this); // Added saveGui
    SaveManagerBrick *saveManager = new SaveManagerBrick(saveHandler, saveGui, this);

    // Toolbar Setup
    QToolBar *toolbar = addToolBar("Tools");
    toolbar->addAction("Bold", boldGui, &BoldBrick::applyBold);
    toolbar->addAction("Italic", italicGui, &ItalicBrick::applyItalic);
    toolbar->addAction("Save", saveGui, &SaveGUIBrick::save); // Fixed signal: triggered -> save

    // Placeholder Example
    setContextMenuPolicy(Qt::CustomContextMenu); // Ensure custom context menu is enabled
    connect(this, &MainWindowBrick::customContextMenuRequested, this, [this](const QPoint &pos) {
        Q_UNUSED(pos); // For now, ignore pos; adjust if PlaceholderBrick needs it
        auto *placeholderBrick = new PlaceholderBrick(edit, this);
        placeholderBrick->insertPlaceholder(0, PlaceholderBrick::Table); // Default pos 0
    });

    // Connections
    connect(boldGui, &BoldBrick::applyBold, boldHandler, &BoldBrick::applyBold);
    connect(italicGui, &ItalicBrick::applyItalic, italicHandler, &ItalicBrick::applyItalic);
    connect(saveGui, &SaveGUIBrick::save, saveHandler, &SaveHandlerBrick::handleSave); // Fixed signal: triggered -> save, handle -> handleSave
    connect(saveHandler, &SaveHandlerBrick::completed, saveManager, &SaveManagerBrick::validate);

    qDebug() << "MainWindowBrick ready.";
}

MainWindowBrick::~MainWindowBrick() {
    // Destructor stub; add cleanup if needed
}

void MainWindowBrick::handleOpenFile() {
    // Stub for open file slot
    qDebug() << "Open file triggered (stub)";
}
