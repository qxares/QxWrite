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

ToolBarBrick::ToolBarBrick(QToolBar *toolBar, QTextEdit *edit, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile, IconBrick *icon, FontBrick *font, QObject *parent)
    : QObject(parent), toolBar(toolBar), targetEdit(edit), insertBrick(insert), saveBrick(save), boldBrick(bold), newFileBrick(newFile), italicBrick(italic), openFileBrick(openFile), iconBrick(icon), fontBrick(font) {
    qDebug() << "ToolBarBrick initialized, toolBar:" << toolBar << ", target edit:" << edit;

    toolBar->addAction(iconBrick->loadIcon(":/icons/icons/file-plus.png"), tr("New"), newFileBrick, &NewFileBrick::newFile);
    toolBar->addAction(iconBrick->loadIcon(":/icons/icons/open.png"), tr("Open"), openFileBrick, &OpenFileBrick::openFile);
    toolBar->addAction(iconBrick->loadIcon(":/icons/icons/save.png"), tr("Save"), saveBrick, &SaveBrick::save);
    toolBar->addSeparator();
    QAction *boldAct = toolBar->addAction(iconBrick->loadIcon(":/icons/icons/bold.png"), tr("Bold"), boldBrick, &BoldBrick::toggleBold);
    boldAct->setCheckable(true);
    QAction *italicAct = toolBar->addAction(iconBrick->loadIcon(":/icons/icons/italic.png"), tr("Italic"), italicBrick, &ItalicBrick::toggleItalic);
    italicAct->setCheckable(true);
    toolBar->addAction(iconBrick->loadIcon(":/icons/icons/font.png"), tr("Font"), fontBrick, &FontBrick::showFontDialog);
    toolBar->addSeparator();
    toolBar->addAction(iconBrick->loadIcon(":/icons/icons/image.png"), tr("Insert Image"), insertBrick, &InsertBrick::insertImage);

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

