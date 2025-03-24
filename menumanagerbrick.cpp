#include "menumanagerbrick.h"
#include <QMenu>
#include <QDebug>

MenuManagerBrick::MenuManagerBrick(QMenuBar *menuBar, QTextEdit *edit, InsertBrick *insert, SaveManagerBrick *save,
                                   BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile,
                                   FontBrick *font, ColorBrick *color, QObject *parent)
    : QObject(parent), m_menuBar(menuBar), m_edit(edit) {
    qDebug() << "MenuManagerBrick initialized, menuBar:" << menuBar;

    QMenu *fileMenu = m_menuBar->addMenu("File");
    fileMenu->addAction("New", newFile, SLOT(newFile()));
    fileMenu->addAction("Open", openFile, SLOT(openFile()));
    fileMenu->addAction(save->saveAction());

    QMenu *formatMenu = m_menuBar->addMenu("Format");
    formatMenu->addAction(bold->boldAction());
    formatMenu->addAction(italic->italicAction());
    formatMenu->addAction(font->getFontAction());
    formatMenu->addAction(color->getColorAction());

    QMenu *insertMenu = m_menuBar->addMenu("Insert");
    insertMenu->addAction("Image", insert, SLOT(insertImage()));

    bold->boldAction()->setCheckable(true);
    italic->italicAction()->setCheckable(true);

    connect(bold->boldAction(), &QAction::toggled, this, [=](bool checked) {
        qDebug() << "Menu toggle states updated - Bold:" << checked << ", Italic:" << italic->italicAction()->isChecked();
    });
    connect(italic->italicAction(), &QAction::toggled, this, [=](bool checked) {
        qDebug() << "Menu toggle states updated - Bold:" << bold->boldAction()->isChecked() << ", Italic:" << checked;
    });

    qDebug() << "Menus set up.";
}

MenuManagerBrick::~MenuManagerBrick() {
}
