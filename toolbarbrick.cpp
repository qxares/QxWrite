#include "toolbarbrick.h"
#include <QDebug>

ToolBarBrick::ToolBarBrick(QWidget *parent) : QObject(parent) {
    toolBar = new QToolBar(parent);
    addToolBarAction("open", "Open", "/home/ares/Downloads/editor/QxWriteProject/icons/open.svg");
    addToolBarAction("save", "Save", "/home/ares/Downloads/editor/QxWriteProject/icons/save.svg");
    addToolBarAction("bold", "Bold", "/home/ares/Downloads/editor/QxWriteProject/icons/bold.svg");
    addToolBarAction("italic", "Italic", "/home/ares/Downloads/editor/QxWriteProject/icons/italic.svg");
    addToolBarAction("font", "Font", "/home/ares/Downloads/editor/QxWriteProject/icons/font.svg");
    addToolBarAction("color", "Color", "/home/ares/Downloads/editor/QxWriteProject/icons/color.svg");
    addToolBarAction("image", "Image", "/home/ares/Downloads/editor/QxWriteProject/icons/image.svg");
    addToolBarAction("alignLeft", "Align Left", "/home/ares/Downloads/editor/QxWriteProject/icons/align-left.svg");
    addToolBarAction("alignCenter", "Align Center", "/home/ares/Downloads/editor/QxWriteProject/icons/align-center.svg");
    addToolBarAction("alignRight", "Align Right", "/home/ares/Downloads/editor/QxWriteProject/icons/align-right.svg");

    qDebug() << "ToolBarBrick initialized with toolbar:" << toolBar;
}

void ToolBarBrick::addToolBarAction(const QString &name, const QString &text, const QString &iconPath) {
    QIcon icon(iconPath);
    if (icon.isNull()) {
        qDebug() << "ToolBarBrick: Failed to load icon at" << iconPath;
    } else {
        qDebug() << "ToolBarBrick: Loaded icon" << text << "from" << iconPath;
    }
    QAction *action = new QAction(icon, text, this);
    actions[name] = action;
    toolBar->addAction(action);
}

QToolBar* ToolBarBrick::getToolBar() const {
    return toolBar;
}

QAction* ToolBarBrick::getAction(const QString &name) const {
    return actions.value(name, nullptr);
}
