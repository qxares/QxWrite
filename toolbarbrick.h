#ifndef TOOLBARBRICK_H
#define TOOLBARBRICK_H

#include <QObject>
#include <QToolBar>
#include "iconbrick.h"
#include "newfilebrick.h"
#include "openfilebrick.h"
#include "savemanagerbrick.h"
#include "boldbrick.h"
#include "italicbrick.h"
#include "fontbrick.h"
#include "colorbrick.h"
#include "insertbrick.h"
#include "alignbrick.h"  // Add this include

class ToolBarBrick : public QObject {
    Q_OBJECT
public:
    explicit ToolBarBrick(QObject *parent = nullptr);
    void setupToolBar(IconBrick *iconBrick, NewFileBrick *newFileBrick, OpenFileBrick *openFileBrick,
                      SaveManagerBrick *saveManager, BoldBrick *boldBrick, ItalicBrick *italicBrick,
                      FontBrick *fontBrick, ColorBrick *colorBrick, InsertBrick *insertBrick,
                      AlignBrick *alignLeftBrick, AlignBrick *alignCenterBrick, AlignBrick *alignRightBrick);
    QToolBar *getToolBar();

private:
    QToolBar *toolBar;
};

#endif // TOOLBARBRICK_H
