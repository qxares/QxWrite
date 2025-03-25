#ifndef TOOLBARBRICK_H
#define TOOLBARBRICK_H

#include <QObject>
#include <QToolBar>
#include "insertbrick.h"
#include "savemanagerbrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"
#include "openfilebrick.h"
#include "iconbrick.h"
#include "fontbrick.h"
#include "colorbrick.h"
#include "alignbrick.h"

class QTextEdit;

class ToolBarBrick : public QObject {
    Q_OBJECT
public:
    ToolBarBrick(QWidget *parent = nullptr);  // Changed to QWidget*
    void setupToolBar(IconBrick *iconBrick, NewFileBrick *newFileBrick, OpenFileBrick *openFileBrick,
                      SaveManagerBrick *saveManager, BoldBrick *boldBrick, ItalicBrick *italicBrick,
                      FontBrick *fontBrick, ColorBrick *colorBrick, InsertBrick *insertBrick,
                      AlignBrick *alignLeftBrick, AlignBrick *alignCenterBrick, AlignBrick *alignRightBrick);
    QToolBar* getToolBar();

private:
    QToolBar *toolBar;
};

#endif // TOOLBARBRICK_H
