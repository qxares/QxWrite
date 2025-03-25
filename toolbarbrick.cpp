#include "toolbarbrick.h"
#include "iconbrick.h"
#include "boldbrick.h"
#include "italicbrick.h"
#include "fontbrick.h"
#include "colorbrick.h"
#include "insertbrick.h"
#include "saveguibrick.h"
#include <QToolBar>
#include <QTextEdit>
#include <QDebug>

ToolBarBrick::ToolBarBrick(QWidget *parent) : QObject(parent) {
    toolBar = new QToolBar(parent);
    iconBrick = new IconBrick(this);
    qDebug() << "IconBrick initialized";

    setupToolBar();
}

QToolBar* ToolBarBrick::getToolBar() {
    return toolBar;
}

QAction* ToolBarBrick::getAction(const QString &name) {
    return actions.value(name, nullptr);
}

void ToolBarBrick::setupToolBar() {
    actions["new"] = toolBar->addAction(iconBrick->getIcon("new"), "New");
    actions["open"] = toolBar->addAction(iconBrick->getIcon("open"), "Open");
    actions["save"] = toolBar->addAction(iconBrick->getIcon("save"), "Save");
    toolBar->addSeparator();
    actions["bold"] = toolBar->addAction(iconBrick->getIcon("bold"), "Bold");
    actions["italic"] = toolBar->addAction(iconBrick->getIcon("italic"), "Italic");
    actions["font"] = toolBar->addAction(iconBrick->getIcon("font"), "Font");
    actions["color"] = toolBar->addAction(iconBrick->getIcon("color"), "Color");
    toolBar->addSeparator();
    actions["image"] = toolBar->addAction(iconBrick->getIcon("image"), "Insert Image");

    actions["bold"]->setCheckable(true);
    actions["italic"]->setCheckable(true);

    qDebug() << "Toolbar set up with icons and toggles.";
}
