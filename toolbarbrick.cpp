#include "toolbarbrick.h"
#include <QToolBar>
#include <QDebug>

ToolBarBrick::ToolBarBrick(QToolBar *toolBar, QTextEdit *edit,
                           InsertBrick *insertBrick, SaveManagerBrick *saveManagerBrick,
                           BoldBrick *boldBrick, NewFileBrick *newFileBrick,
                           ItalicBrick *italicBrick, OpenFileBrick *openFileBrick,
                           IconBrick *iconBrick, FontBrick *fontBrick,
                           ColorBrick *colorBrick, QObject *parent)
    : QObject(parent) {
    QAction *newAct = new QAction("New", this);
    newAct->setIcon(iconBrick->getIcon("new"));
    connect(newAct, &QAction::triggered, newFileBrick, &NewFileBrick::newFile);
    toolBar->addAction(newAct);

    QAction *openAct = new QAction("Open", this);
    openAct->setIcon(iconBrick->getIcon("open"));
    connect(openAct, &QAction::triggered, openFileBrick, &OpenFileBrick::openFile);
    toolBar->addAction(openAct);

    QAction *saveAct = saveManagerBrick->saveAction();
    saveAct->setIcon(iconBrick->getIcon("save"));
    toolBar->addAction(saveAct);

    QAction *boldAct = boldBrick->boldAction();
    boldAct->setIcon(iconBrick->getIcon("bold"));
    toolBar->addAction(boldAct);

    QAction *italicAct = italicBrick->italicAction();
    italicAct->setIcon(iconBrick->getIcon("italic"));
    toolBar->addAction(italicAct);

    QAction *fontAct = fontBrick->getFontAction();
    fontAct->setIcon(iconBrick->getIcon("font"));
    toolBar->addAction(fontAct);

    QAction *colorAct = colorBrick->getColorAction();
    colorAct->setIcon(iconBrick->getIcon("color"));
    toolBar->addAction(colorAct);

    QAction *imageAct = new QAction("Insert Image", this);
    imageAct->setIcon(iconBrick->getIcon("image"));
    connect(imageAct, &QAction::triggered, insertBrick, &InsertBrick::insertImage);
    toolBar->addAction(imageAct);

    qDebug() << "Toolbar set up with icons and toggles.";
}

ToolBarBrick::~ToolBarBrick() {
    // Empty is fine—QObject cleans up children
}
