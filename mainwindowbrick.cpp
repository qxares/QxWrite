#include "mainwindowbrick.h"
#include <QTextEdit>
#include <QDebug>
#include "boldbrick.h" // Covers BoldBrick logic (function, handler, and GUI for now)
#include "italicfunctionbrick.h"
#include "italichandlerbrick.h"
#include "italicguibrick.h"
#include "italicmanagerbrick.h"
#include "savefunctionbrick.h"
#include "savehandlerbrick.h"
#include "saveguibrick.h"
#include "savemanagerbrick.h"
#include "guimanagerbrick.h"
#include "placeholderbrick.h"

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "MainWindowBrick starting...";
    edit = new QTextEdit(this);
    setCentralWidget(edit);
    resize(800, 600);

    // Bold Action
    BoldBrick *boldFunction = new BoldBrick(edit, this);
    BoldBrick *boldHandler = new BoldBrick(edit, this);
    BoldBrick *boldGui = new BoldBrick(edit, this); // Temp fix: was BoldGuiBrick

    // Italic Action
    ItalicFunctionBrick *italicFunction = new ItalicFunctionBrick(edit, this);
    ItalicHandlerBrick *italicHandler = new ItalicHandlerBrick(italicFunction, this);
    ItalicGuiBrick *italicGui = new ItalicGuiBrick(this);
    ItalicManagerBrick *italicManager = new ItalicManagerBrick(italicHandler, italicGui, this);

    // Save Action
    SaveFunctionBrick *saveFunction = new SaveFunctionBrick(edit, this);
    SaveHandlerBrick *saveHandler = new SaveHandlerBrick(saveFunction, this);
    SaveGuiBrick *saveGui = new SaveGuiBrick(this);
    SaveManagerBrick *saveManager = new SaveManagerBrick(saveHandler, saveGui, this);

    // GUI Manager
    GuiManagerBrick *guiManager = new GuiManagerBrick(menuBar(), addToolBar("Tools"), this);
    guiManager->addGuiBrick(boldGui); // Might need adjustment if BoldBrick isn’t GUI-compatible
    guiManager->addGuiBrick(italicGui);
    guiManager->addGuiBrick(saveGui);

    // Placeholder Example
    connect(this, &MainWindowBrick::customContextMenuRequested, this, [this](int pos) {
        auto *placeholderBrick = new PlaceholderBrick(edit, this);
        placeholderBrick->insertPlaceholder(pos, PlaceholderBrick::Table);
    });

    // Connections
    connect(boldGui, &BoldBrick::applyBold, boldHandler, &BoldBrick::applyBold); // Temp fix: no manager yet
    connect(italicGui, &ItalicGuiBrick::triggered, italicHandler, &ItalicHandlerBrick::handle);
    connect(italicHandler, &ItalicHandlerBrick::completed, italicManager, &ItalicManagerBrick::validate);
    connect(saveGui, &SaveGuiBrick::triggered, saveHandler, &SaveHandlerBrick::handle);
    connect(saveHandler, &SaveHandlerBrick::completed, saveManager, &SaveManagerBrick::validate);

    qDebug() << "MainWindowBrick ready.";
}
