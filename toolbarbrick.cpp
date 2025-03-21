#include "toolbarbrick.h"
#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QDebug>
#include "insertbrick.h"
#include "savebrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"
#include "openfilebrick.h"
#include "iconbrick.h"

ToolBarBrick::ToolBarBrick(QToolBar *bar, QTextEdit *edit, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile, IconBrick *iconBrick, QObject *parent)
    : QObject(parent), toolBar(bar), targetEdit(edit), insertBrick(insert), saveBrick(save), boldBrick(bold), newFileBrick(newFile), italicBrick(italic), openFileBrick(openFile), iconBrick(iconBrick), boldAction(nullptr), italicAction(nullptr) {
    qDebug() << "ToolBarBrick initialized, toolBar:" << toolBar << ", target edit:" << targetEdit;
}

void ToolBarBrick::setupToolBar() {
    qDebug() << "Setting up toolbar...";
    if (!toolBar) {
        qDebug() << "No toolbar provided!";
        return;
    }
    QAction *newAction = toolBar->addAction(iconBrick->getIcon("file-plus"), tr("New"));
    newAction->setToolTip(tr("New Document"));
    connect(newAction, &QAction::triggered, newFileBrick, &NewFileBrick::newFile);

    QAction *openAction = toolBar->addAction(iconBrick->getIcon("open"), tr("Open"));
    openAction->setToolTip(tr("Open File"));
    connect(openAction, &QAction::triggered, openFileBrick, &OpenFileBrick::openFile);

    QAction *saveAction = toolBar->addAction(iconBrick->getIcon("save"), tr("Save"));
    saveAction->setToolTip(tr("Save File"));
    connect(saveAction, &QAction::triggered, saveBrick, &SaveBrick::save);

    boldAction = toolBar->addAction(iconBrick->getIcon("bold"), tr("Bold"));
    boldAction->setToolTip(tr("Toggle Bold"));
    boldAction->setCheckable(true);
    connect(boldAction, &QAction::toggled, boldBrick, &BoldBrick::toggleBold);
    connect(boldBrick, &BoldBrick::boldToggled, boldAction, &QAction::setChecked);

    italicAction = toolBar->addAction(iconBrick->getIcon("italic"), tr("Italic"));
    italicAction->setToolTip(tr("Toggle Italic"));
    italicAction->setCheckable(true);
    connect(italicAction, &QAction::toggled, italicBrick, &ItalicBrick::toggleItalic);
    connect(italicBrick, &ItalicBrick::italicToggled, italicAction, &QAction::setChecked);

    QAction *insertImageAction = toolBar->addAction(iconBrick->getIcon("image"), tr("Insert Image"));
    insertImageAction->setToolTip(tr("Insert Image"));
    connect(insertImageAction, &QAction::triggered, insertBrick, &InsertBrick::insertImage);

    if (targetEdit) {
        connect(targetEdit, &QTextEdit::cursorPositionChanged, this, &ToolBarBrick::updateToggleStates);
        connect(newFileBrick, &NewFileBrick::newFileCreated, this, &ToolBarBrick::updateToggleStates);
        updateToggleStates();
    } else {
        qDebug() << "ToolBarBrick: No QTextEdit provided for toggle updates!";
    }

    qDebug() << "Toolbar set up with icons and toggles.";
}

void ToolBarBrick::updateToggleStates() {
    if (!targetEdit) return;
    QTextCursor cursor = targetEdit->textCursor();
    boldAction->setChecked(cursor.charFormat().fontWeight() == QFont::Bold);
    italicAction->setChecked(cursor.charFormat().fontItalic());
}
