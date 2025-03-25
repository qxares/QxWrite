#include "mainwindowbrick.h"
#include "iconbrick.h"
#include <QVBoxLayout>
#include <QToolBar>
#include <QDebug>

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "MainWindowBrick starting...";

    setMinimumSize(800, 600);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    textEdit = new QTextEdit(this);
    layout->addWidget(textEdit);
    setCentralWidget(centralWidget);

    IconBrick *iconBrick = new IconBrick(this);
    iconBrick->registerIcons();

    saveManager = new SaveManagerBrick(textEdit, this);
    insertBrick = new InsertBrick(textEdit, this);
    boldBrick = new BoldBrick(textEdit, this);
    newFileBrick = new NewFileBrick(textEdit, this);
    italicBrick = new ItalicBrick(textEdit, this);
    openFileBrick = new OpenFileBrick(textEdit, this);
    fontBrick = new FontBrick(textEdit, this);
    colorBrick = new ColorBrick(textEdit, this);
    alignLeftBrick = new AlignBrick(textEdit, AlignBrick::AlignLeft, this);      // Add these
    alignCenterBrick = new AlignBrick(textEdit, AlignBrick::AlignCenter, this);
    alignRightBrick = new AlignBrick(textEdit, AlignBrick::AlignRight, this);

    toolBar = new ToolBarBrick(this);
    toolBar->setupToolBar(iconBrick, newFileBrick, openFileBrick, saveManager, boldBrick, italicBrick, fontBrick, colorBrick, insertBrick, alignLeftBrick, alignCenterBrick, alignRightBrick);
    addToolBar(toolBar->getToolBar());

    menuManager = new MenuManagerBrick(this);
    menuManager->setupMenus(iconBrick, newFileBrick, openFileBrick, saveManager, boldBrick, italicBrick, fontBrick, colorBrick, insertBrick, alignLeftBrick, alignCenterBrick, alignRightBrick);
    setMenuBar(menuManager->getMenuBar());

    qDebug() << "MainWindowBrick ready.";
}
