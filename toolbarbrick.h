#ifndef TOOLBARBRICK_H
#define TOOLBARBRICK_H
#include <QObject>
#include <QToolBar>
#include <QTextEdit>
#include "insertbrick.h"
#include "savebrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"
#include "openfilebrick.h"
#include "iconbrick.h"
#include "fontbrick.h"
#include "colorbrick.h"
class ToolBarBrick : public QObject {
    Q_OBJECT
public:
    ToolBarBrick(QToolBar *toolBar, QTextEdit *edit, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile, IconBrick *icon, FontBrick *font, ColorBrick *color, QObject *parent = nullptr);
    void setupToolBar();
private slots:
    void updateToggleStates();
private:
    QToolBar *m_toolBar;
    QTextEdit *m_textEdit;
    InsertBrick *m_insertBrick;
    SaveBrick *m_saveBrick;
    BoldBrick *m_boldBrick;
    NewFileBrick *m_newFileBrick;
    ItalicBrick *m_italicBrick;
    OpenFileBrick *m_openFileBrick;
    IconBrick *m_iconBrick;
    FontBrick *m_fontBrick;
    ColorBrick *m_colorBrick;
    QAction *m_boldAct;
    QAction *m_italicAct;
};
#endif // TOOLBARBRICK_H
