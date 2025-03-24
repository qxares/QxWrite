#ifndef TOOLBARBRICK_H
#define TOOLBARBRICK_H

#include <QObject>
#include <QToolBar>
#include <QTextEdit>
#include "insertbrick.h"
#include "savemanagerbrick.h"
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
    ToolBarBrick(QToolBar *toolBar, QTextEdit *edit, InsertBrick *insert, SaveManagerBrick *save,
                 BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile,
                 IconBrick *icon, FontBrick *font, ColorBrick *color, QObject *parent = nullptr);
    ~ToolBarBrick();

private:
    QToolBar *m_toolBar;
    QTextEdit *m_edit;
};

#endif // TOOLBARBRICK_H
