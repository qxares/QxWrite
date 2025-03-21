#include "mainwindowbrick.h"
#include <QTextEdit>
#include <QMenuBar>
#include "insertbrick.h"
#include "savebrick.h"
#include "menumanagerbrick.h"
#include <QDebug>

MainWindowBrick::MainWindowBrick(QWidget *parent)
    : QMainWindow(parent), textEdit(new QTextEdit(this)) {
    qDebug() << "MainWindowBrick starting...";
    textEdit->setAcceptRichText(true);
    setCentralWidget(textEdit);
    setMinimumSize(800, 600);

    InsertBrick *insert = new InsertBrick(textEdit, this);
    SaveBrick *save = new SaveBrick(textEdit, this);
    MenuManagerBrick *menu = new MenuManagerBrick(menuBar(), insert, save, this);
    menu->setupMenus();

    qDebug() << "MainWindowBrick ready.";
}

MainWindowBrick::~MainWindowBrick() {}

