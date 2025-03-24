#include "toolbarbrick.h"
#include <QDebug>

ToolBarBrick::ToolBarBrick(QToolBar *toolBar, QTextEdit *edit, InsertBrick *insert, SaveManagerBrick *save,
                           BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile,
                           IconBrick *icon, FontBrick *font, ColorBrick *color, QObject *parent)
    : QObject(parent), m_toolBar(toolBar), m_edit(edit) {
    qDebug() << "ToolBarBrick initialized, toolBar:" << toolBar << ", target edit:" << edit;

    m_toolBar->addAction(icon->loadIcon("new"), "New", newFile, SLOT(newFile()));
    m_toolBar->addAction(icon->loadIcon("open"), "Open", openFile, SLOT(openFile()));
    m_toolBar->addAction(save->saveAction());
    m_toolBar->addAction(bold->boldAction());
    m_toolBar->addAction(italic->italicAction());
    m_toolBar->addAction(font->getFontAction());
    m_toolBar->addAction(color->getColorAction());
    m_toolBar->addAction(icon->loadIcon("image"), "Image", insert, SLOT(insertImage()));

    bold->boldAction()->setCheckable(true);
    italic->italicAction()->setCheckable(true);

    connect(bold->boldAction(), &QAction::toggled, this, [=](bool checked) {
        qDebug() << "Toggle states updated - Bold:" << checked << ", Italic:" << italic->italicAction()->isChecked();
    });
    connect(italic->italicAction(), &QAction::toggled, this, [=](bool checked) {
        qDebug() << "Toggle states updated - Bold:" << bold->boldAction()->isChecked() << ", Italic:" << checked;
    });

    qDebug() << "Toolbar set up with icons and toggles.";
}

ToolBarBrick::~ToolBarBrick() {
}
