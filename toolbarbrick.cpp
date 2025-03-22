#include "toolbarbrick.h"
#include <QDebug>

ToolBarBrick::ToolBarBrick(QToolBar *toolBar, QTextEdit *edit, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile, IconBrick *icon, FontBrick *font, ColorBrick *color, QObject *parent)
    : QObject(parent), m_toolBar(toolBar), m_textEdit(edit), m_insertBrick(insert), m_saveBrick(save), m_boldBrick(bold), m_newFileBrick(newFile), m_italicBrick(italic), m_openFileBrick(openFile), m_iconBrick(icon), m_fontBrick(font), m_colorBrick(color) {
    qDebug() << "ToolBarBrick initialized, toolBar:" << m_toolBar << ", target edit:" << m_textEdit;
    setupToolBar();
}

void ToolBarBrick::setupToolBar() {
    QAction *newAct = m_toolBar->addAction(m_iconBrick->loadIcon("new"), "New");
    QAction *openAct = m_toolBar->addAction(m_iconBrick->loadIcon("open"), "Open");
    QAction *saveAct = m_toolBar->addAction(m_iconBrick->loadIcon("save"), "Save");
    m_boldAct = m_toolBar->addAction(m_iconBrick->loadIcon("bold"), "Bold");
    m_italicAct = m_toolBar->addAction(m_iconBrick->loadIcon("italic"), "Italic");
    QAction *fontAct = m_toolBar->addAction(m_iconBrick->loadIcon("font"), "Font");
    QAction *colorAct = m_toolBar->addAction(m_iconBrick->loadIcon("color"), "Color");
    QAction *imageAct = m_toolBar->addAction(m_iconBrick->loadIcon("image"), "Image");
    connect(newAct, &QAction::triggered, m_newFileBrick, &NewFileBrick::newFile);
    connect(openAct, &QAction::triggered, m_openFileBrick, &OpenFileBrick::openFile);
    connect(saveAct, &QAction::triggered, m_saveBrick, &SaveBrick::save);
    connect(m_boldAct, &QAction::triggered, m_boldBrick, &BoldBrick::toggleBold);
    connect(m_italicAct, &QAction::triggered, m_italicBrick, &ItalicBrick::toggleItalic);
    connect(fontAct, &QAction::triggered, m_fontBrick, &FontBrick::showFontDialog);
    connect(colorAct, &QAction::triggered, m_colorBrick, &ColorBrick::showColorDialog);
    connect(imageAct, &QAction::triggered, m_insertBrick, &InsertBrick::insertImage);
    m_boldAct->setCheckable(true);
    m_italicAct->setCheckable(true);
    updateToggleStates();
    qDebug() << "Toolbar set up with icons and toggles.";
}

void ToolBarBrick::updateToggleStates() {
    QTextCharFormat fmt = m_textEdit->currentCharFormat();
    bool bold = fmt.fontWeight() == QFont::Bold;
    bool italic = fmt.font().italic();
    m_boldAct->setChecked(bold);
    m_italicAct->setChecked(italic);
    qDebug() << "Toggle states updated - Bold:" << bold << ", Italic:" << italic;
}
