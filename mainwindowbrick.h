#ifndef MAINWINDOWBRICK_H
#define MAINWINDOWBRICK_H

#include <QMainWindow>
#include "menumanagerbrick.h"
#include "toolbarbrick.h"
#include "insertbrick.h"
#include "savemanagerbrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"
#include "openfilebrick.h"
#include "iconbrick.h"
#include "fontbrick.h"
#include "colorbrick.h"
#include "dialogbrick.h"
#include "alignbrick.h"  // Added

class QTextEdit;
class ToolBarBrick;

class MainWindowBrick : public QMainWindow {
    Q_OBJECT
public:
    MainWindowBrick(QWidget *parent = nullptr);
    ~MainWindowBrick();

private:
    QTextEdit *textEdit;
    MenuManagerBrick *menuManager;
    ToolBarBrick *toolBar;
    InsertBrick *insertBrick;
    SaveManagerBrick *saveManager;
    BoldBrick *boldBrick;
    NewFileBrick *newFileBrick;
    ItalicBrick *italicBrick;
    OpenFileBrick *openFileBrick;
    IconBrick *iconBrick;
    FontBrick *fontBrick;
    ColorBrick *colorBrick;
    DialogBrick *dialogBrick;
    AlignBrick *alignLeftBrick;    // Added
    AlignBrick *alignCenterBrick;  // Added
    AlignBrick *alignRightBrick;   // Added
};

#endif // MAINWINDOWBRICK_H
