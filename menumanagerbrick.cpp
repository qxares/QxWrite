#include "menumanagerbrick.h"
#include <QDebug>

MenuManagerBrick::MenuManagerBrick(QObject *parent) : QObject(parent) {
    menuBar = new QMenuBar();
    qDebug() << "MenuManagerBrick initialized, menuBar:" << menuBar;
}

void MenuManagerBrick::setupMenus(IconBrick *iconBrick, NewFileBrick *newFileBrick, OpenFileBrick *openFileBrick,
                                  SaveManagerBrick *saveManager, BoldBrick *boldBrick, ItalicBrick *italicBrick,
                                  FontBrick *fontBrick, ColorBrick *colorBrick, InsertBrick *insertBrick,
                                  AlignBrick *alignLeftBrick, AlignBrick *alignCenterBrick, AlignBrick *alignRightBrick) {
    QMenu *fileMenu = menuBar->addMenu("File");
    fileMenu->addAction(iconBrick->getIcon("new"), "New", newFileBrick, &NewFileBrick::newFile);
    fileMenu->addAction(iconBrick->getIcon("open"), "Open", openFileBrick, &OpenFileBrick::openFile);
    fileMenu->addAction(iconBrick->getIcon("save"), "Save", saveManager, &SaveManagerBrick::saveFile);
    fileMenu->addAction("Save As", saveManager, &SaveManagerBrick::saveFileAs);

    QMenu *editMenu = menuBar->addMenu("Edit");

    QMenu *formatMenu = menuBar->addMenu("Format");
    formatMenu->addAction(iconBrick->getIcon("bold"), "Bold", boldBrick, &BoldBrick::toggleBold);
    formatMenu->addAction(iconBrick->getIcon("italic"), "Italic", italicBrick, &ItalicBrick::toggleItalic);
    formatMenu->addAction(iconBrick->getIcon("font"), "Font", fontBrick, &FontBrick::changeFont);
    formatMenu->addAction(iconBrick->getIcon("color"), "Color", colorBrick, &ColorBrick::changeColor);
    formatMenu->addSeparator();
    formatMenu->addAction(iconBrick->getIcon("align-left"), "Align Left", alignLeftBrick, &AlignBrick::alignText);
    formatMenu->addAction(iconBrick->getIcon("align-center"), "Align Center", alignCenterBrick, &AlignBrick::alignText);
    formatMenu->addAction(iconBrick->getIcon("align-right"), "Align Right", alignRightBrick, &AlignBrick::alignText);

    QMenu *insertMenu = menuBar->addMenu("Insert");
    insertMenu->addAction(iconBrick->getIcon("image"), "Image", insertBrick, &InsertBrick::insertImage);

    qDebug() << "Menus set up.";
}

QMenuBar *MenuManagerBrick::getMenuBar() {
    return menuBar;
}
