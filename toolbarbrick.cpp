#include "toolbarbrick.h"
#include <QToolBar>
#include <QAction>
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
    QAction *newAction = toolBar->addAction(tr("New"));
    connect(newAction, &QAction::triggered, newFileBrick, &NewFileBrick::newFile);

    QAction *saveAction = toolBar->addAction(tr("Save"));
    connect(saveAction, &QAction::triggered, saveBrick, &SaveBrick::save);

    QAction *boldAction = toolBar->addAction(tr("Bold"));
    connect(boldAction, &QAction::triggered, boldBrick, &BoldBrick::toggleBold);

    QAction *italicAction = toolBar->addAction(tr("Italic"));
    connect(italicAction, &QAction::triggered, italicBrick, &ItalicBrick::toggleItalic);

    QAction *insertImageAction = toolBar->addAction(tr("Insert Image"));
    connect(insertImageAction, &QAction::triggered, insertBrick, &InsertBrick::insertImage);

    qDebug() << "Toolbar set up.";
}
