#include "mainwindowbrick.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QToolBar>
#include "insertbrick.h"
#include "savebrick.h"
#include "menumanagerbrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "toolbarbrick.h"
#include "italicbrick.h"
#include "openfilebrick.h"
#include <QDebug>

MainWindowBrick::MainWindowBrick(QWidget *parent)
    : QMainWindow(parent), textEdit(new QTextEdit(this)) {
    qDebug() << "MainWindowBrick starting...";
    textEdit->setAcceptRichText(true);
    setCentralWidget(textEdit);
    setMinimumSize(800, 600);

    insertBrick = new InsertBrick(textEdit, this);
    saveBrick = new SaveBrick(textEdit, this);
    boldBrick = new BoldBrick(textEdit, this);
    newFileBrick = new NewFileBrick(textEdit, this);
    italicBrick = new ItalicBrick(textEdit, this);
    openFileBrick = new OpenFileBrick(textEdit, this);
    menuManagerBrick = new MenuManagerBrick(menuBar(), insertBrick, saveBrick, boldBrick, newFileBrick, italicBrick, openFileBrick, this);
    toolBarBrick = new ToolBarBrick(addToolBar("Main Toolbar"), textEdit, insertBrick, saveBrick, boldBrick, newFileBrick, italicBrick, openFileBrick, this);

    menuManagerBrick->setupMenus();
    toolBarBrick->setupToolBar();

    qDebug() << "MainWindowBrick ready.";
}

MainWindowBrick::~MainWindowBrick() {}

