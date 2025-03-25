#include "toolbarbrick.h"
#include <QToolBar>
#include <QAction>
#include <QDebug>

ToolBarBrick::ToolBarBrick(QWidget *parent) : QObject(parent) {
    toolBar = new QToolBar("Main Toolbar", parent);
    toolBar->setMovable(false);

    newAction = new QAction(QIcon(":/icons/icons/file-plus.svg"), "New", this);
    newAction->setToolTip("New Document");
    if (!newAction->icon().isNull()) qDebug() << "ToolBarBrick: New icon loaded";
    else newAction->setIcon(QIcon::fromTheme("document-new"));
    toolBar->addAction(newAction);

    openAction = new QAction(QIcon(":/icons/icons/open.svg"), "Open", this);
    openAction->setToolTip("Open Document");
    if (!openAction->icon().isNull()) qDebug() << "ToolBarBrick: Open icon loaded";
    else openAction->setIcon(QIcon::fromTheme("document-open"));
    toolBar->addAction(openAction);

    saveAction = new QAction(QIcon(":/icons/icons/save.svg"), "Save", this);
    saveAction->setToolTip("Save Document");
    if (!saveAction->icon().isNull()) qDebug() << "ToolBarBrick: Save icon loaded";
    else saveAction->setIcon(QIcon::fromTheme("document-save"));
    toolBar->addAction(saveAction);

    boldAction = new QAction(QIcon(":/icons/icons/bold.svg"), "Bold", this);
    boldAction->setToolTip("Bold Text");
    if (!boldAction->icon().isNull()) qDebug() << "ToolBarBrick: Bold icon loaded";
    else boldAction->setIcon(QIcon::fromTheme("format-text-bold"));
    toolBar->addAction(boldAction);

    italicAction = new QAction(QIcon(":/icons/icons/italic.svg"), "Italic", this);
    italicAction->setToolTip("Italic Text");
    if (!italicAction->icon().isNull()) qDebug() << "ToolBarBrick: Italic icon loaded";
    else italicAction->setIcon(QIcon::fromTheme("format-text-italic"));
    toolBar->addAction(italicAction);

    fontAction = new QAction(QIcon(":/icons/icons/font.svg"), "Font", this);
    fontAction->setToolTip("Change Font");
    if (!fontAction->icon().isNull()) qDebug() << "ToolBarBrick: Font icon loaded";
    else fontAction->setIcon(QIcon::fromTheme("font"));
    toolBar->addAction(fontAction);

    colorAction = new QAction(QIcon(":/icons/icons/color.svg"), "Color", this);
    colorAction->setToolTip("Text Color");
    if (!colorAction->icon().isNull()) qDebug() << "ToolBarBrick: Color icon loaded";
    else colorAction->setIcon(QIcon::fromTheme("color-select"));
    toolBar->addAction(colorAction);

    imageAction = new QAction(QIcon(":/icons/icons/image.svg"), "Image", this);
    imageAction->setToolTip("Insert Image");
    if (!imageAction->icon().isNull()) qDebug() << "ToolBarBrick: Image icon loaded";
    else imageAction->setIcon(QIcon::fromTheme("insert-image"));
    toolBar->addAction(imageAction);

    alignLeftAction = new QAction(QIcon(":/icons/icons/align-left.svg"), "Align Left", this);
    alignLeftAction->setToolTip("Align Left");
    if (!alignLeftAction->icon().isNull()) qDebug() << "ToolBarBrick: Align Left icon loaded";
    else alignLeftAction->setIcon(QIcon::fromTheme("format-justify-left"));
    toolBar->addAction(alignLeftAction);

    alignCenterAction = new QAction(QIcon(":/icons/icons/align-center.svg"), "Align Center", this);
    alignCenterAction->setToolTip("Align Center");
    if (!alignCenterAction->icon().isNull()) qDebug() << "ToolBarBrick: Align Center icon loaded";
    else alignCenterAction->setIcon(QIcon::fromTheme("format-justify-center"));
    toolBar->addAction(alignCenterAction);

    alignRightAction = new QAction(QIcon(":/icons/icons/align-right.svg"), "Align Right", this);
    alignRightAction->setToolTip("Align Right");
    if (!alignRightAction->icon().isNull()) qDebug() << "ToolBarBrick: Align Right icon loaded";
    else alignRightAction->setIcon(QIcon::fromTheme("format-justify-right"));
    toolBar->addAction(alignRightAction);

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
    qDebug() << "ToolBarBrick: Action" << name << "not found";
    return nullptr;
}
