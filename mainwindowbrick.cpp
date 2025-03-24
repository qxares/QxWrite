#include "mainwindowbrick.h"
#include <QTextEdit>
#include <QToolBar>
#include <QMenuBar>
#include <QDebug>

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "MainWindowBrick starting...";
    setFixedSize(800, 600);

    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    QToolBar *toolBar = new QToolBar(this);
    addToolBar(toolBar);

    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    iconBrick = new IconBrick(this);
    saveManagerBrick = new SaveManagerBrick(textEdit, this);
    insertBrick = new InsertBrick(textEdit, this);
    boldBrick = new BoldBrick(textEdit, this);
    newFileBrick = new NewFileBrick(textEdit, this);
    italicBrick = new ItalicBrick(textEdit, this);
    openFileBrick = new OpenFileBrick(textEdit, new DialogBrick(this), this);
    fontBrick = new FontBrick(textEdit, this);
    colorBrick = new ColorBrick(textEdit, this);

    toolBarBrick = new ToolBarBrick(
        toolBar, textEdit, insertBrick, saveManagerBrick, boldBrick, newFileBrick,
        italicBrick, openFileBrick, iconBrick, fontBrick, colorBrick, this
    );

    menuManagerBrick = new MenuManagerBrick(
        menuBar, textEdit, insertBrick, saveManagerBrick, boldBrick, newFileBrick,
        italicBrick, openFileBrick, fontBrick, colorBrick, this
    );

    qDebug() << "MainWindowBrick ready.";
}

MainWindowBrick::~MainWindowBrick() {
}
