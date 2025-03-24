#ifndef MAINWINDOWBRICK_H
#define MAINWINDOWBRICK_H

#include <QMainWindow>
#include "toolbarbrick.h"
#include "menumanagerbrick.h"
#include "savemanagerbrick.h"
#include "insertbrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"
#include "openfilebrick.h"
#include "iconbrick.h"
#include "fontbrick.h"
#include "colorbrick.h"

class MainWindowBrick : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindowBrick(QWidget *parent = nullptr);
    ~MainWindowBrick();

private:
    QTextEdit *textEdit;
    ToolBarBrick *toolBarBrick;
    MenuManagerBrick *menuManagerBrick;
    SaveManagerBrick *saveManagerBrick;
    InsertBrick *insertBrick;
    BoldBrick *boldBrick;
    NewFileBrick *newFileBrick;
    ItalicBrick *italicBrick;
    OpenFileBrick *openFileBrick;
    IconBrick *iconBrick;
    FontBrick *fontBrick;
    ColorBrick *colorBrick;
};

#endif // MAINWINDOWBRICK_H
