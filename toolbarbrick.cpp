#include "toolbarbrick.h"
#include <QDebug>

ToolBarBrick::ToolBarBrick(QWidget *parent) : QObject(parent) {  // Changed to QWidget*
    toolBar = new QToolBar(parent);
    qDebug() << "ToolBarBrick initialized, toolBar:" << toolBar;
}

void ToolBarBrick::setupToolBar(IconBrick *iconBrick, NewFileBrick *newFileBrick, OpenFileBrick *openFileBrick,
                                SaveManagerBrick *saveManager, BoldBrick *boldBrick, ItalicBrick *italicBrick,
                                FontBrick *fontBrick, ColorBrick *colorBrick, InsertBrick *insertBrick,
                                AlignBrick *alignLeftBrick, AlignBrick *alignCenterBrick, AlignBrick *alignRightBrick) {
    toolBar->addAction(iconBrick->getIcon("new"), "New", newFileBrick, &NewFileBrick::newFile);
    toolBar->addAction(iconBrick->getIcon("open"), "Open", openFileBrick, &OpenFileBrick::openFile);
    toolBar->addAction(iconBrick->getIcon("save"), "Save", saveManager, &SaveManagerBrick::saveAs);
    toolBar->addSeparator();
    toolBar->addAction(iconBrick->getIcon("bold"), "Bold", boldBrick, &BoldBrick::toggleBold);
    toolBar->addAction(iconBrick->getIcon("italic"), "Italic", italicBrick, &ItalicBrick::toggleItalic);
    toolBar->addAction(iconBrick->getIcon("font"), "Font", fontBrick, &FontBrick::showFontDialog);
    toolBar->addAction(iconBrick->getIcon("color"), "Color", colorBrick, &ColorBrick::showColorDialog);
    toolBar->addAction(iconBrick->getIcon("image"), "Insert Image", insertBrick, &InsertBrick::insertImage);
    toolBar->addSeparator();
    toolBar->addAction(iconBrick->getIcon("align-left"), "Align Left", alignLeftBrick, &AlignBrick::align);
    toolBar->addAction(iconBrick->getIcon("align-center"), "Align Center", alignCenterBrick, &AlignBrick::align);
    toolBar->addAction(iconBrick->getIcon("align-right"), "Align Right", alignRightBrick, &AlignBrick::align);

    qDebug() << "Toolbar set up.";
}

QToolBar* ToolBarBrick::getToolBar() {
    return toolBar;
}
