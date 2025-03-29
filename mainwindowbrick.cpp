#include "mainwindowbrick.h"
#include <QTextEdit>
#include <QDebug>
#include <QToolBar>
#include "boldbrick.h"
#include "italicbrick.h"
#include "savefunctionbrick.h"
#include "savehandlerbrick.h"
#include "saveguibrick.h"
#include "savemanagerbrick.h"
#include "placeholderbrick.h"

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "MainWindowBrick starting...";
    
    // Setup QTextEdit as central widget
    edit = new QTextEdit(this);
    edit->setMinimumSize(600, 400); // Ensure it has a visible size
    setCentralWidget(edit);
    resize(800, 600);
    setWindowTitle("QxWrite"); // Give it a title for clarity

    // Toolbar Setup
    QToolBar *toolbar = addToolBar("Tools");
    toolbar->setMovable(false); // Lock it in place for now

    // Bold Action
    BoldBrick *boldBrick = new BoldBrick(edit, this);
    QAction *boldAction = toolbar->addAction("Bold", boldBrick, &BoldBrick::applyBold);

    // Italic Action
    ItalicBrick *italicBrick = new ItalicBrick(edit, this);
    QAction *italicAction = toolbar->addAction("Italic", italicBrick, &ItalicBrick::applyItalic);

    // Save Action
    SaveFunctionBrick *saveFunction = new SaveFunctionBrick(edit, this);
    SaveGUIBrick *saveGui = new SaveGUIBrick(edit, this);
    SaveHandlerBrick *saveHandler = new SaveHandlerBrick(saveFunction, saveGui, this);
    SaveManagerBrick *saveManager = new SaveManagerBrick(edit, this);
    QAction *saveAction = toolbar->addAction("Save", saveManager, &SaveManagerBrick::triggerSave);

    // Placeholder Context Menu
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &MainWindowBrick::customContextMenuRequested, this, [this](const QPoint &pos) {
        PlaceholderBrick *placeholderBrick = new PlaceholderBrick(edit, this);
        placeholderBrick->insertPlaceholder(edit->textCursor().position(), PlaceholderBrick::Table);
    });

    // Connections (simplified, no redundant handlers)
    connect(saveHandler, &SaveHandlerBrick::completed, saveManager, &SaveManagerBrick::validate);

    qDebug() << "MainWindowBrick ready.";
}

MainWindowBrick::~MainWindowBrick() {
    // Destructor stub; add cleanup if needed
}

void MainWindowBrick::handleOpenFile() {
    qDebug() << "Open file triggered (stub)";
}
