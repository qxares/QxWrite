#ifndef MAINWINDOWBRICK_H
#define MAINWINDOWBRICK_H

#include <QMainWindow>

class QTextEdit;
class InsertBrick;
class SaveBrick;
class MenuManagerBrick;
class BoldBrick;
class NewFileBrick;
class ToolBarBrick;
class ItalicBrick;
class OpenFileBrick;
class IconBrick;

class MainWindowBrick : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindowBrick(QWidget *parent = nullptr);
    ~MainWindowBrick();

private:
    QTextEdit *textEdit;
    InsertBrick *insertBrick;
    SaveBrick *saveBrick;
    BoldBrick *boldBrick;
    NewFileBrick *newFileBrick;
    ItalicBrick *italicBrick;
    OpenFileBrick *openFileBrick;
    IconBrick *iconBrick;
    MenuManagerBrick *menuManagerBrick;
    ToolBarBrick *toolBarBrick;
};

#endif // MAINWINDOWBRICK_H
