#include "toolbarbrick.h"
#include <QToolBar>
#include <QTextEdit>
#include <QTextCharFormat>
#include <QDebug>
#include "insertbrick.h"
#include "savebrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"
#include "openfilebrick.h"
#include "iconbrick.h"
#include "fontbrick.h"
#include "colorbrick.h"

ToolBarBrick::ToolBarBrick(QToolBar *toolBar, QTextEdit *edit, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile, IconBrick *icon, FontBrick *font, ColorBrick *color, QObject *parent)
    : QObject(parent), toolBar(toolBar), targetEdit(edit), insertBrick(insert), saveBrick(save), boldBrick(bold), newFileBrick(newFile), italicBrick(italic), openFileBrick(openFile), iconBrick(icon), fontBrick(font), colorBrick(color) {
    qDebug() << "ToolBarBrick initialized, toolBar:" << toolBar << ", target edit:" << edit;

    toolBar->addAction(iconBrick->loadIcon("new"), tr("New"), newFileBrick, &NewFileBrick::newFile);
    toolBar->addAction(iconBrick->loadIcon("open"), tr("Open"), openFileBrick, &OpenFileBrick::openFile);
    toolBar->addAction(iconBrick->loadIcon("save"), tr("Save"), saveBrick, &SaveBrick::save);
    toolBar->addSeparator();
    QAction *boldAct = toolBar->addAction(iconBrick->loadIcon("bold"), tr("Bold"), boldBrick, &BoldBrick::toggleBold);
    boldAct->setCheckable(true);
    QAction *italicAct = toolBar->addAction(iconBrick->loadIcon("italic"), tr("Italic"), italicBrick, &ItalicBrick::toggleItalic);
    italicAct->setCheckable(true);
    toolBar->addAction(iconBrick->loadIcon("font"), tr("Font"), fontBrick, &FontBrick::showFontDialog);
    toolBar->addAction(iconBrick->loadIcon("color"), tr("Color"), colorBrick, &ColorBrick::showColorDialog);
    toolBar->addSeparator();
    toolBar->addAction(iconBrick->loadIcon("image"), tr("Insert Image"), insertBrick, &InsertBrick::insertImage);

    connect(targetEdit, &QTextEdit::cursorPositionChanged, this, &ToolBarBrick::updateToggleStates);
    updateToggleStates();

    qDebug() << "Toolbar set up with icons and toggles.";
}

void ToolBarBrick::updateToggleStates() {
    QTextCursor cursor = targetEdit->textCursor();
    QTextCharFormat format = cursor.charFormat();
    bool isBold = format.fontWeight() == QFont::Bold;
    bool isItalic = format.fontItalic();
    QList<QAction*> actions = toolBar->actions();
    for (QAction *action : actions) {
        if (action->text() == tr("Bold")) action->setChecked(isBold);
        if (action->text() == tr("Italic")) action->setChecked(isItalic);
    }
    qDebug() << "Toggle states updated - Bold:" << isBold << ", Italic:" << isItalic;
}

