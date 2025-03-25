#include "menumanagerbrick.h"
#include <QDebug>

MenuManagerBrick::MenuManagerBrick(QWidget *parent) : QObject(parent) {
    menuBar = new QMenuBar(parent);
    qDebug() << "MenuManagerBrick initialized, menuBar:" << menuBar;
}

void MenuManagerBrick::setupMenus(IconBrick *iconBrick, NewFileBrick *newFileBrick, OpenFileBrick *openFileBrick,
                                  SaveManagerBrick *saveManager, BoldBrick *boldBrick, ItalicBrick *italicBrick,
                                  FontBrick *fontBrick, ColorBrick *colorBrick, InsertBrick *insertBrick,
                                  AlignBrick *alignLeftBrick, AlignBrick *alignCenterBrick, AlignBrick *alignRightBrick) {
    QMenu *fileMenu = menuBar->addMenu("File");
    fileMenu->addAction(iconBrick->getIcon("new"), "New", newFileBrick, &NewFileBrick::newFile);
    fileMenu->addAction(iconBrick->getIcon("open"), "Open", openFileBrick, &OpenFileBrick::openFile);
    fileMenu->addAction(iconBrick->getIcon("save"), "Save", saveManager, &SaveManagerBrick::saveAs);
    fileMenu->addAction("Save As", saveManager, &SaveManagerBrick::saveAs);

    QMenu *editMenu = menuBar->addMenu("Edit");
    editMenu->addAction(iconBrick->getIcon("image"), "Insert Image", insertBrick, &InsertBrick::insertImage);

    QMenu *formatMenu = menuBar->addMenu("Format");
    formatMenu->addAction(iconBrick->getIcon("bold"), "Bold", boldBrick, &BoldBrick::toggleBold);
    formatMenu->addAction(iconBrick->getIcon("italic"), "Italic", italicBrick, &ItalicBrick::toggleItalic);
    formatMenu->addAction(iconBrick->getIcon("font"), "Font", fontBrick, &FontBrick::showFontDialog);  // Fixed to showFontDialog
    formatMenu->addAction(iconBrick->getIcon("color"), "Color", colorBrick, &ColorBrick::showColorDialog);  // Assume showColorDialog
    formatMenu->addSeparator();
    formatMenu->addAction(iconBrick->getIcon("align-left"), "Align Left", alignLeftBrick, &AlignBrick::align);
    formatMenu->addAction(iconBrick->getIcon("align-center"), "Align Center", alignCenterBrick, &AlignBrick::align);
    formatMenu->addAction(iconBrick->getIcon("align-right"), "Align Right", alignRightBrick, &AlignBrick::align);

    qDebug() << "Menus set up.";
}

QMenuBar* MenuManagerBrick::getMenuBar() {
    return menuBar;
}
