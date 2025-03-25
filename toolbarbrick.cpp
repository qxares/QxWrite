#include "toolbarbrick.h"
#include <QDebug>

ToolBarBrick::ToolBarBrick(QObject *parent) : QObject(parent) {
    toolBar = new QToolBar();
}

void ToolBarBrick::setupToolBar(IconBrick *iconBrick, NewFileBrick *newFileBrick, OpenFileBrick *openFileBrick,
                                SaveManagerBrick *saveManager, BoldBrick *boldBrick, ItalicBrick *italicBrick,
                                FontBrick *fontBrick, ColorBrick *colorBrick, InsertBrick *insertBrick,
                                AlignBrick *alignLeftBrick, AlignBrick *alignCenterBrick, AlignBrick *alignRightBrick) {
    toolBar->addAction(iconBrick->getIcon("new"), "New", newFileBrick, &NewFileBrick::newFile);
    toolBar->addAction(iconBrick->getIcon("open"), "Open", openFileBrick, &OpenFileBrick::openFile);
    toolBar->addAction(iconBrick->getIcon("save"), "Save", saveManager, &SaveManagerBrick::saveFile);
    toolBar->addSeparator();
    toolBar->addAction(iconBrick->getIcon("bold"), "Bold", boldBrick, &BoldBrick::toggleBold);
    toolBar->addAction(iconBrick->getIcon("italic"), "Italic", italicBrick, &ItalicBrick::toggleItalic);
    toolBar->addAction(iconBrick->getIcon("font"), "Font", fontBrick, &FontBrick::changeFont);
    toolBar->addAction(iconBrick->getIcon("color"), "Color", colorBrick, &ColorBrick::changeColor);
    toolBar->addSeparator();
    toolBar->addAction(iconBrick->getIcon("align-left"), "Align Left", alignLeftBrick, &AlignBrick::alignText);
    toolBar->addAction(iconBrick->getIcon("align-center"), "Align Center", alignCenterBrick, &AlignBrick::alignText);
    toolBar->addAction(iconBrick->getIcon("align-right"), "Align Right", alignRightBrick, &AlignBrick::alignText);
    toolBar->addSeparator();
    toolBar->addAction(iconBrick->getIcon("image"), "Insert Image", insertBrick, &InsertBrick::insertImage);

    qDebug() << "Toolbar set up with icons and toggles.";
}

QToolBar *ToolBarBrick::getToolBar() {
    return toolBar;
}
