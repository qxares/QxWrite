#ifndef MAINWINDOWBRICK_H
#define MAINWINDOWBRICK_H

#include <QMainWindow>

class QTextEdit;
class QToolBar;
class QMenuBar;
class InsertBrick;
class SaveManagerBrick;
class BoldBrick;
class NewFileBrick;
class ItalicBrick;
class OpenFileBrick;
class IconBrick;
class ToolBarBrick;
class MenuManagerBrick;
class FontBrick;
class ColorBrick;
class DialogBrick;  // Add this

class MainWindowBrick : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindowBrick(QWidget *parent = nullptr);
    ~MainWindowBrick() override = default;

private:
    QTextEdit *textEdit;
    QToolBar *toolBar;
    QMenuBar *menuBar;
    IconBrick *iconBrick;
    SaveManagerBrick *saveManagerBrick;
    InsertBrick *insertBrick;
    BoldBrick *boldBrick;
    NewFileBrick *newFileBrick;
    ItalicBrick *italicBrick;
    OpenFileBrick *openFileBrick;
    FontBrick *fontBrick;
    ColorBrick *colorBrick;
    ToolBarBrick *toolBarBrick;
    MenuManagerBrick *menuManagerBrick;
    DialogBrick *dialogBrick;  // Add this
};

#endif // MAINWINDOWBRICK_H
