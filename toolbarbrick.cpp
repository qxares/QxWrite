#include "toolbarbrick.h"
#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QDebug>
#include "insertbrick.h"
#include "savebrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"

ToolBarBrick::ToolBarBrick(QToolBar *bar, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, QObject *parent)
    : QObject(parent), toolBar(bar), insertBrick(insert), saveBrick(save), boldBrick(bold), newFileBrick(newFile), italicBrick(italic) {
    qDebug() << "ToolBarBrick initialized, toolBar:" << toolBar;
}

void ToolBarBrick::setupToolBar() {
    qDebug() << "Setting up toolbar...";
    if (!toolBar) {
        qDebug() << "No toolbar provided!";
        return;
    }
    QAction *newAction = toolBar->addAction(QIcon(":/icons/file-plus.png"), tr("New"));
    connect(newAction, &QAction::triggered, newFileBrick, &NewFileBrick::newFile);

    QAction *saveAction = toolBar->addAction(QIcon(":/icons/save.png"), tr("Save"));
    connect(saveAction, &QAction::triggered, saveBrick, &SaveBrick::save);

    QAction *boldAction = toolBar->addAction(QIcon(":/icons/bold.png"), tr("Bold"));
    connect(boldAction, &QAction::triggered, boldBrick, &BoldBrick::toggleBold);

    QAction *italicAction = toolBar->addAction(QIcon(":/icons/italic.png"), tr("Italic"));
    connect(italicAction, &QAction::triggered, italicBrick, &ItalicBrick::toggleItalic);

    QAction *insertImageAction = toolBar->addAction(QIcon(":/icons/image.png"), tr("Insert Image"));
    connect(insertImageAction, &QAction::triggered, insertBrick, &InsertBrick::insertImage);

    qDebug() << "Toolbar set up with icons.";
}
