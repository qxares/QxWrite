#ifndef MAINWINDOWBRICK_H
#define MAINWINDOWBRICK_H

#include <QMainWindow>

class ToolBarBrick;
class MenuManagerBrick;
class DocumentWindow;
class NewFileBrick;

class MainWindowBrick : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindowBrick(QWidget *parent = nullptr);
    ~MainWindowBrick();

private:
    void setupUI();

    ToolBarBrick *toolbarBrick;
    MenuManagerBrick *menuManagerBrick;
    DocumentWindow *documentWindow;
};

#endif // MAINWINDOWBRICK_H
