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
    MenuManagerBrick *menuManagerBrick;
    ToolBarBrick *toolBarBrick;
    OpenFileBrick *openFileBrick;
};

#endif // MAINWINDOWBRICK_H
