#ifndef MENUMANAGERBRICK_H
#define MENUMANAGERBRICK_H

#include <QObject>
#include <QMenuBar>
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

class MenuManagerBrick : public QObject {
    Q_OBJECT
public:
    explicit MenuManagerBrick(QObject *parent = nullptr);
    void setupMenus(IconBrick *iconBrick, NewFileBrick *newFileBrick, OpenFileBrick *openFileBrick,
                    SaveManagerBrick *saveManager, BoldBrick *boldBrick, ItalicBrick *italicBrick,
                    FontBrick *fontBrick, ColorBrick *colorBrick, InsertBrick *insertBrick,
                    AlignBrick *alignLeftBrick, AlignBrick *alignCenterBrick, AlignBrick *alignRightBrick);
    QMenuBar *getMenuBar();

private:
    QMenuBar *menuBar;
};

#endif // MENUMANAGERBRICK_H
