#include "mainwindowbrick.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QToolBar>
#include <QDebug>

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "MainWindowBrick starting...";
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    insertBrick = new InsertBrick(textEdit, this);
    dialogBrick = new DialogBrick(this);
    saveBrick = new SaveBrick(textEdit, dialogBrick, this);
    boldBrick = new BoldBrick(textEdit, this);
    newFileBrick = new NewFileBrick(textEdit, this);
    italicBrick = new ItalicBrick(textEdit, this);
    openFileBrick = new OpenFileBrick(textEdit, dialogBrick, this);
    iconBrick = new IconBrick(this);
    menuManagerBrick = new MenuManagerBrick(menuBar(), insertBrick, saveBrick, boldBrick, newFileBrick, italicBrick, openFileBrick, this);
    toolBarBrick = new ToolBarBrick(new QToolBar(this), textEdit, insertBrick, saveBrick, boldBrick, newFileBrick, italicBrick, openFileBrick, iconBrick, this);

    qDebug() << "Setting up menus...";
    menuManagerBrick->setupMenus();
    qDebug() << "Menus set up.";

    qDebug() << "Setting up toolbar...";
    toolBarBrick->setupToolBar();
    qDebug() << "Toolbar set up with icons and toggles.";

    qDebug() << "MainWindowBrick ready.";
}

MainWindowBrick::~MainWindowBrick() {}

