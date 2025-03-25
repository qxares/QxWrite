#include "toolbarbrick.h"
#include <QToolBar>
#include <QAction>
#include <QDebug>

ToolBarBrick::ToolBarBrick(QWidget *parent) : QObject(parent) {
    toolBar = new QToolBar("Main Toolbar", parent);
    toolBar->setMovable(false);

    newAction = new QAction(QIcon(":/icons/new.png"), "New", this);
    newAction->setToolTip("New Document");
    toolBar->addAction(newAction);

    openAction = new QAction(QIcon(":/icons/open.png"), "Open", this);
    openAction->setToolTip("Open Document");
    toolBar->addAction(openAction);

    qDebug() << "ToolBarBrick initialized with toolbar:" << toolBar;
}

QToolBar* ToolBarBrick::getToolBar() const {
    return toolBar;
}

QAction* ToolBarBrick::getAction(const QString &name) const {
    if (name == "new") return newAction;
    if (name == "open") return openAction;
    qDebug() << "ToolBarBrick: Action" << name << "not found";
    return nullptr;
}
