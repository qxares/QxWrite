#ifndef MAINWINDOWBRICK_H
#define MAINWINDOWBRICK_H

#include <QMainWindow>
#include <QTextEdit>
#include "menumanagerbrick.h"
#include "toolbarbrick.h"
#include "insertbrick.h"
#include "boldbrick.h"
#include "italicbrick.h"
#include "newfilebrick.h"
#include "openfilebrick.h"
#include "fontbrick.h"
#include "colorbrick.h"
#include "savemanagerbrick.h"
#include "alignbrick.h"  // Add this include

class MainWindowBrick : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindowBrick(QWidget *parent = nullptr);

private:
    QTextEdit *textEdit;
    MenuManagerBrick *menuManager;
    ToolBarBrick *toolBar;
    InsertBrick *insertBrick;
    BoldBrick *boldBrick;
    ItalicBrick *italicBrick;
    NewFileBrick *newFileBrick;
    OpenFileBrick *openFileBrick;
    FontBrick *fontBrick;
    ColorBrick *colorBrick;
    SaveManagerBrick *saveManager;
    AlignBrick *alignLeftBrick;    // Add these
    AlignBrick *alignCenterBrick;
    AlignBrick *alignRightBrick;
};

#endif // MAINWINDOWBRICK_H
