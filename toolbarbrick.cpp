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

ToolBarBrick::ToolBarBrick(QToolBar *bar, QTextEdit *edit, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile, QObject *parent)
    : QObject(parent), toolBar(bar), targetEdit(edit), insertBrick(insert), saveBrick(save), boldBrick(bold), newFileBrick(newFile), italicBrick(italic), openFileBrick(openFile), boldAction(nullptr), italicAction(nullptr) {
    qDebug() << "ToolBarBrick initialized, toolBar:" << toolBar << ", target edit:" << targetEdit;
}

void ToolBarBrick::setupToolBar() {
    qDebug() << "Setting up toolbar...";
    if (!toolBar) {
        qDebug() << "No toolbar provided!";
        return;
    }
    QAction *newAction = toolBar->addAction(QIcon(":/icons/file-plus.png"), tr("New"));
    connect(newAction, &QAction::triggered, newFileBrick, &NewFileBrick::newFile);

    QAction *openAction = toolBar->addAction(QIcon(":/icons/file.png"), tr("Open"));
    connect(openAction, &QAction::triggered, openFileBrick, &OpenFileBrick::openFile);

    QAction *saveAction = toolBar->addAction(QIcon(":/icons/save.png"), tr("Save"));
    connect(saveAction, &QAction::triggered, saveBrick, &SaveBrick::save);

    boldAction = toolBar->addAction(QIcon(":/icons/bold.png"), tr("Bold"));
    boldAction->setCheckable(true);
    connect(boldAction, &QAction::toggled, boldBrick, &BoldBrick::toggleBold);
    connect(boldBrick, &BoldBrick::boldToggled, boldAction, &QAction::setChecked);

    italicAction = toolBar->addAction(QIcon(":/icons/italic.png"), tr("Italic"));
    italicAction->setCheckable(true);
    connect(italicAction, &QAction::toggled, italicBrick, &ItalicBrick::toggleItalic);
    connect(italicBrick, &ItalicBrick::italicToggled, italicAction, &QAction::setChecked);

    QAction *insertImageAction = toolBar->addAction(QIcon(":/icons/image.png"), tr("Insert Image"));
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
