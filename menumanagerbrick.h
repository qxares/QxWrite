#ifndef MENUMANAGERBRICK_H
#define MENUMANAGERBRICK_H

#include <QObject>
#include <QMenuBar>
#include <QTextEdit>
#include "insertbrick.h"
#include "savemanagerbrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"
#include "openfilebrick.h"
#include "fontbrick.h"
#include "colorbrick.h"

class MenuManagerBrick : public QObject {
    Q_OBJECT
public:
    MenuManagerBrick(QMenuBar *menuBar, QTextEdit *edit, InsertBrick *insert, SaveManagerBrick *save,
                     BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile,
                     FontBrick *font, ColorBrick *color, QObject *parent = nullptr);
    ~MenuManagerBrick();

private:
    QMenuBar *m_menuBar;
    QTextEdit *m_edit;
};

#endif // MENUMANAGERBRICK_H
