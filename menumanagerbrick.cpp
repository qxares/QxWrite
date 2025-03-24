#include "menumanagerbrick.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTextEdit>
#include <QTextCharFormat>
#include <QApplication>
#include <QDebug>
#include "insertbrick.h"
#include "savebrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"
#include "openfilebrick.h"
#include "fontbrick.h"
#include "colorbrick.h"

MenuManagerBrick::MenuManagerBrick(QMenuBar *menuBar, QTextEdit *edit, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile, FontBrick *font, ColorBrick *color, QObject *parent)
    : QObject(parent), menuBar(menuBar), targetEdit(edit), insertBrick(insert), saveBrick(save), boldBrick(bold), newFileBrick(newFile), italicBrick(italic), openFileBrick(openFile), fontBrick(font), colorBrick(color), boldAct(nullptr), italicAct(nullptr) {
    qDebug() << "MenuManagerBrick initialized, menuBar:" << menuBar;

    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(tr("&New"), newFileBrick, &NewFileBrick::newFile);
    fileMenu->addAction(tr("&Open"), openFileBrick, &OpenFileBrick::openFile);
    fileMenu->addAction(tr("&Save"), saveBrick, &SaveBrick::save);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("E&xit"), qApp, &QApplication::quit);

    QMenu *editMenu = menuBar->addMenu(tr("&Edit"));
    boldAct = editMenu->addAction(tr("&Bold"), boldBrick, &BoldBrick::toggleBold);
    boldAct->setCheckable(true);
    italicAct = editMenu->addAction(tr("&Italic"), italicBrick, &ItalicBrick::toggleItalic);
    italicAct->setCheckable(true);
    editMenu->addAction(fontBrick->getFontAction());
    editMenu->addAction(colorBrick->getColorAction());

    QMenu *insertMenu = menuBar->addMenu(tr("&Insert"));
    insertMenu->addAction(tr("&Image"), insertBrick, &InsertBrick::insertImage);

    connect(targetEdit, &QTextEdit::cursorPositionChanged, this, &MenuManagerBrick::updateToggleStates);
    updateToggleStates();

    qDebug() << "Menus set up.";
}

void MenuManagerBrick::updateToggleStates() {
    QTextCursor cursor = targetEdit->textCursor();
    QTextCharFormat format = cursor.charFormat();
    bool isBold = format.fontWeight() == QFont::Bold;
    bool isItalic = format.fontItalic();
    boldAct->setChecked(isBold);
    italicAct->setChecked(isItalic);
    qDebug() << "Menu toggle states updated - Bold:" << isBold << ", Italic:" << isItalic;
}

