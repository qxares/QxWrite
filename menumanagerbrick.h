#ifndef MENUMANAGERBRICK_H
#define MENUMANAGERBRICK_H

#include <QObject>
#include <QMenuBar>
#include "insertbrick.h"
#include "savemanagerbrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"
#include "openfilebrick.h"
#include "iconbrick.h"
#include "fontbrick.h"
#include "colorbrick.h"
#include "alignbrick.h"  // Added

class MenuManagerBrick : public QObject {
    Q_OBJECT
public:
    MenuManagerBrick(QWidget *parent = nullptr);
    void setupMenus(IconBrick *iconBrick, NewFileBrick *newFileBrick, OpenFileBrick *openFileBrick,
                    SaveManagerBrick *saveManager, BoldBrick *boldBrick, ItalicBrick *italicBrick,
                    FontBrick *fontBrick, ColorBrick *colorBrick, InsertBrick *insertBrick,
                    AlignBrick *alignLeftBrick, AlignBrick *alignCenterBrick, AlignBrick *alignRightBrick);  // Added
    QMenuBar* getMenuBar();

private:
    QMenuBar *menuBar;
};

#endif // MENUMANAGERBRICK_H
