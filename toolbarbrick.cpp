#include "toolbarbrick.h"
#include <QDebug>

ToolBarBrick::ToolBarBrick(QWidget *parent) : QObject(parent) {
    toolBar = new QToolBar(parent);
    newAction = addAction("new", "New", ":/icons/plus.svg");
    openAction = addAction("open", "Open", ":/icons/open.svg");
    saveAction = addAction("save", "Save", ":/icons/save.svg");
    boldAction = addAction("bold", "Bold", ":/icons/bold.svg");
    italicAction = addAction("italic", "Italic", ":/icons/italic.svg");
    fontAction = addAction("font", "Font", ":/icons/font.svg");
    colorAction = addAction("color", "Color", ":/icons/color.svg");
    imageAction = addAction("image", "Insert Image", ":/icons/image.svg");
    alignLeftAction = addAction("alignLeft", "Align Left", ":/icons/align-left.svg");
    alignCenterAction = addAction("alignCenter", "Align Center", ":/icons/align-center.svg");
    alignRightAction = addAction("alignRight", "Align Right", ":/icons/align-right.svg");
    tableAction = addAction("table", "Insert Table", ""); // No icon yet
    qDebug() << "ToolBarBrick initialized with toolbar:" << toolBar;
}

QToolBar* ToolBarBrick::getToolBar() const {
    return toolBar;
}

QAction* ToolBarBrick::getAction(const QString &name) const {
    if (name == "new") return newAction;
    if (name == "open") return openAction;
    if (name == "save") return saveAction;
    if (name == "bold") return boldAction;
    if (name == "italic") return italicAction;
    if (name == "font") return fontAction;
    if (name == "color") return colorAction;
    if (name == "image") return imageAction;
    if (name == "alignLeft") return alignLeftAction;
    if (name == "alignCenter") return alignCenterAction;
    if (name == "alignRight") return alignRightAction;
    if (name == "table") return tableAction;
    return nullptr;
}

QAction* ToolBarBrick::addAction(const QString &name, const QString &text, const QString &iconPath) {
    QAction *action = new QAction(text, this);
    if (!iconPath.isEmpty()) {
        action->setIcon(QIcon(iconPath));
        qDebug() << "ToolBarBrick:" << text << "icon loaded from" << iconPath;
    } else {
        qDebug() << "ToolBarBrick:" << text << "no icon specified";
    }
    toolBar->addAction(action);
    return action;
}
