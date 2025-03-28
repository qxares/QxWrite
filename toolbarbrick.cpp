#include "toolbarbrick.h"
#include <QDebug>

ToolBarBrick::ToolBarBrick(QWidget *parent) : QObject(parent) {
    toolBar = new QToolBar(parent);
    newAction = addAction("new", "New", ":/icons/icons/file-plus.svg");
    openAction = addAction("open", "Open", ":/icons/icons/folder-open.svg");
    saveAction = addAction("save", "Save", ":/icons/icons/save.svg");
    boldAction = addAction("bold", "Bold", ":/icons/icons/bold.svg");
    italicAction = addAction("italic", "Italic", ":/icons/icons/italic.svg");
    fontAction = addAction("font", "Font", ":/icons/icons/font.svg");
    colorAction = addAction("color", "Color", ":/icons/icons/palette.svg");
    imageAction = addAction("image", "Insert Image", ":/icons/icons/image.svg");
    alignLeftAction = addAction("alignLeft", "Align Left", ":/icons/icons/align-left.svg");
    alignCenterAction = addAction("alignCenter", "Align Center", ":/icons/icons/align-center.svg");
    alignRightAction = addAction("alignRight", "Align Right", ":/icons/icons/align-right.svg");
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
        qDebug() << "ToolBarBrick:" << text << "icon loaded";
    } else {
        qDebug() << "ToolBarBrick:" << text << "no icon specified";
    }
    toolBar->addAction(action);
    return action;
}
