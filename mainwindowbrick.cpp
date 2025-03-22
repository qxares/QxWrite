#include "mainwindowbrick.h"
#include "insertbrick.h"
#include "savebrick.h"
#include "menumanagerbrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"
#include "openfilebrick.h"
#include "toolbarbrick.h"
#include "iconbrick.h"
#include "dialogbrick.h"
#include "fontbrick.h"
#include "colorbrick.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QDebug>

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "MainWindowBrick starting...";

    edit = new QTextEdit(this);
    insertBrick = new InsertBrick(edit, this);
    dialogBrick = new DialogBrick(this);
    saveBrick = new SaveBrick(edit, dialogBrick, this);
    boldBrick = new BoldBrick(edit, this);
    newFileBrick = new NewFileBrick(edit, this);
    italicBrick = new ItalicBrick(edit, this);
    openFileBrick = new OpenFileBrick(edit, dialogBrick, this);
    iconBrick = new IconBrick(this);
    fontBrick = new FontBrick(edit, this);
    colorBrick = new ColorBrick(edit, this);

    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    menuManagerBrick = new MenuManagerBrick(menuBar, edit, insertBrick, saveBrick, boldBrick, newFileBrick, italicBrick, openFileBrick, fontBrick, colorBrick, this);

    QToolBar *toolBar = new QToolBar(this);
    addToolBar(toolBar);
    toolBarBrick = new ToolBarBrick(toolBar, edit, insertBrick, saveBrick, boldBrick, newFileBrick, italicBrick, openFileBrick, iconBrick, fontBrick, colorBrick, this);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(edit);
    setCentralWidget(centralWidget);

    resize(800, 600);
    qDebug() << "MainWindowBrick ready.";
}

