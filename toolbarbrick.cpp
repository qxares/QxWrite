#include "toolbarbrick.h"
#include "insertbrick.h"
#include "savebrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"
#include "openfilebrick.h"
#include "iconbrick.h"
#include <QToolBar>
#include <QAction>
#include <QTextEdit>
#include <QTextCharFormat>
#include <QDebug>

ToolBarBrick::ToolBarBrick(QToolBar *toolBar, QTextEdit *edit, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile, IconBrick *iconBrick, QObject *parent)
    : QObject(parent), toolBar(toolBar), targetEdit(edit), insertBrick(insert), saveBrick(save), boldBrick(bold), newFileBrick(newFile), italicBrick(italic), openFileBrick(openFile), iconBrick(iconBrick), boldAct(nullptr), italicAct(nullptr) {
    qDebug() << "ToolBarBrick initialized, toolBar:" << toolBar << ", target edit:" << targetEdit;

    toolBar->addAction(iconBrick->getIcon("file-plus"), tr("New"), newFileBrick, &NewFileBrick::newFile);
    toolBar->addAction(iconBrick->getIcon("open"), tr("Open"), openFileBrick, &OpenFileBrick::openFile);
    toolBar->addAction(iconBrick->getIcon("save"), tr("Save"), saveBrick, &SaveBrick::save);
    toolBar->addSeparator();
    boldAct = toolBar->addAction(iconBrick->getIcon("bold"), tr("Bold"), boldBrick, &BoldBrick::toggleBold);
    boldAct->setCheckable(true);
    italicAct = toolBar->addAction(iconBrick->getIcon("italic"), tr("Italic"), italicBrick, &ItalicBrick::toggleItalic);
    italicAct->setCheckable(true);
    toolBar->addSeparator();
    toolBar->addAction(iconBrick->getIcon("image"), tr("Insert Image"), insertBrick, &InsertBrick::insertImage);

    connect(targetEdit, &QTextEdit::cursorPositionChanged, this, &ToolBarBrick::updateToggleStates);
    updateToggleStates(); // Initial state

    qDebug() << "Toolbar set up with icons and toggles.";
}

void ToolBarBrick::updateToggleStates() {
    QTextCursor cursor = targetEdit->textCursor();
    QTextCharFormat format = cursor.charFormat();
    bool isBold = format.fontWeight() == QFont::Bold;
    bool isItalic = format.fontItalic();
    boldAct->setChecked(isBold);
    italicAct->setChecked(isItalic);
    qDebug() << "Toggle states updated - Bold:" << isBold << ", Italic:" << isItalic;
}

