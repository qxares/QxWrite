#ifndef MAINWINDOWBRICK_H
#define MAINWINDOWBRICK_H

#include <QMainWindow>

class QTextEdit;
class QMenuBar;
class QToolBar;
class InsertBrick;
class SaveBrick;
class MenuManagerBrick;
class BoldBrick;
class NewFileBrick;
class ItalicBrick;
class OpenFileBrick;
class ToolBarBrick;
class IconBrick;
class DialogBrick;
class FontBrick;
class ColorBrick;

class MainWindowBrick : public QMainWindow {
    Q_OBJECT
public:
    MainWindowBrick(QWidget *parent = nullptr);
    virtual ~MainWindowBrick() = default;

private:
    QTextEdit *edit;
    InsertBrick *insertBrick;
    SaveBrick *saveBrick;
    MenuManagerBrick *menuManagerBrick;
    BoldBrick *boldBrick;
    NewFileBrick *newFileBrick;
    ItalicBrick *italicBrick;
    OpenFileBrick *openFileBrick;
    ToolBarBrick *toolBarBrick;
    IconBrick *iconBrick;
    DialogBrick *dialogBrick;
    FontBrick *fontBrick;
    ColorBrick *colorBrick;
};

#endif // MAINWINDOWBRICK_H

