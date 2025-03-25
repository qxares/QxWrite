#include "mainwindowbrick.h"
#include <QTextEdit>
#include <QToolBar>
#include <QMenuBar>
#include <QDebug>
#include "dialogbrick.h"
#include "insertbrick.h"
#include "savemanagerbrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"
#include "openfilebrick.h"
#include "iconbrick.h"
#include "toolbarbrick.h"
#include "menumanagerbrick.h"
#include "fontbrick.h"
#include "colorbrick.h"

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "MainWindowBrick starting...";
    setFixedSize(800, 600);

    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    toolBar = new QToolBar(this);
    addToolBar(toolBar);

    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    dialogBrick = new DialogBrick(this);  // Add this
    iconBrick = new IconBrick(this);
    saveManagerBrick = new SaveManagerBrick(textEdit, this);
    insertBrick = new InsertBrick(textEdit, dialogBrick, this);  // Update this
    boldBrick = new BoldBrick(textEdit, this);
    newFileBrick = new NewFileBrick(textEdit, this);
    italicBrick = new ItalicBrick(textEdit, this);
    openFileBrick = new OpenFileBrick(textEdit, dialogBrick, this);  // Use existing dialogBrick
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
