#include "toolbarbrick.h"
#include <QToolBar>
#include <QAction>
#include <QDebug>

ToolBarBrick::ToolBarBrick(QWidget *parent) : QObject(parent) {
    toolBar = new QToolBar("Main Toolbar", parent);
    toolBar->setMovable(false);

    newAction = new QAction(QIcon(":/icons/icons/new.png"), "New", this);
    newAction->setToolTip("New Document");
    if (!newAction->icon().isNull()) {
        qDebug() << "ToolBarBrick: New icon loaded successfully";
    } else {
        qDebug() << "ToolBarBrick: Failed to load icons/new.png";
        newAction->setIcon(QIcon::fromTheme("document-new")); // Fallback
    }
    toolBar->addAction(newAction);

    openAction = new QAction(QIcon(":/icons/icons/open.png"), "Open", this);
    openAction->setToolTip("Open Document");
    if (!openAction->icon().isNull()) {
        qDebug() << "ToolBarBrick: Open icon loaded successfully";
    } else {
        qDebug() << "ToolBarBrick: Failed to load icons/open.png";
        openAction->setIcon(QIcon::fromTheme("document-open")); // Fallback
    }
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
