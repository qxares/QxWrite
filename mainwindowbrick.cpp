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
#include <QDebug>

MainWindowBrick::MainWindowBrick(QWidget *parent)
    : QMainWindow(parent), textEdit(new QTextEdit(this)) {
    qDebug() << "MainWindowBrick starting...";
    textEdit->setAcceptRichText(true);
    setCentralWidget(textEdit);
    setMinimumSize(800, 600);

    InsertBrick *insert = new InsertBrick(textEdit, this);
    SaveBrick *save = new SaveBrick(textEdit, this);
    BoldBrick *bold = new BoldBrick(textEdit, this);
    NewFileBrick *newFile = new NewFileBrick(textEdit, this);
    ItalicBrick *italic = new ItalicBrick(textEdit, this);
    MenuManagerBrick *menu = new MenuManagerBrick(menuBar(), insert, save, bold, newFile, italic, this);
    ToolBarBrick *toolbar = new ToolBarBrick(addToolBar("Main Toolbar"), insert, save, bold, newFile, italic, this);
    menu->setupMenus();
    toolbar->setupToolBar();

    qDebug() << "MainWindowBrick ready.";
}

MainWindowBrick::~MainWindowBrick() {}

