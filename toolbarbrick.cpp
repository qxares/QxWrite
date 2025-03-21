#include "toolbarbrick.h"
#include "insertbrick.h"
#include "savebrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"
#include "openfilebrick.h"
#include "iconbrick.h"
#include <QToolBar>
#include <QAction>
#include <QDebug>

ToolBarBrick::ToolBarBrick(QToolBar *toolBar, QTextEdit *edit, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile, IconBrick *iconBrick, QObject *parent)
    : QObject(parent), toolBar(toolBar), targetEdit(edit), insertBrick(insert), saveBrick(save), boldBrick(bold), newFileBrick(newFile), italicBrick(italic), openFileBrick(openFile), iconBrick(iconBrick) {
    qDebug() << "ToolBarBrick initialized, toolBar:" << toolBar << ", target edit:" << targetEdit;

    QAction *newAct = toolBar->addAction(iconBrick->getIcon("file-plus"), tr("New"), newFileBrick, &NewFileBrick::newFile);
    QAction *openAct = toolBar->addAction(iconBrick->getIcon("open"), tr("Open"), openFileBrick, &OpenFileBrick::openFile);
    QAction *saveAct = toolBar->addAction(iconBrick->getIcon("save"), tr("Save"), saveBrick, &SaveBrick::save);
    toolBar->addSeparator();
    QAction *boldAct = toolBar->addAction(iconBrick->getIcon("bold"), tr("Bold"), boldBrick, &BoldBrick::toggleBold);
    boldAct->setCheckable(true);
    QAction *italicAct = toolBar->addAction(iconBrick->getIcon("italic"), tr("Italic"), italicBrick, &ItalicBrick::toggleItalic);
    italicAct->setCheckable(true);
    toolBar->addSeparator();
    QAction *insertImageAct = toolBar->addAction(iconBrick->getIcon("image"), tr("Insert Image"), insertBrick, &InsertBrick::insertImage);

    qDebug() << "Toolbar set up with icons and toggles.";
}

