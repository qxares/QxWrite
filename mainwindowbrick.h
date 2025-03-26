#ifndef MAINWINDOWBRICK_H
#define MAINWINDOWBRICK_H

#include <QObject>
#include <QMainWindow>
#include <QMdiArea>

class ToolBarBrick;
class MenuManagerBrick;
class NewFileBrick;
class OpenFileBrick;
class SaveManagerBrick;
class BoldBrick;
class ItalicBrick;
class FontBrick;
class ColorBrick;
class InsertBrick;
class AlignBrick;
class DocumentWindow;
class DocumentHandlerBrick;

class MainWindowBrick : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindowBrick(QWidget *parent = nullptr);
    ~MainWindowBrick();

private:
    ToolBarBrick *toolBarBrick;
    MenuManagerBrick *menuManagerBrick;
    NewFileBrick *newFileBrick;
    OpenFileBrick *openFileBrick;
    SaveManagerBrick *saveManagerBrick;
    BoldBrick *boldBrick;
    ItalicBrick *italicBrick;
    FontBrick *fontBrick;
    ColorBrick *colorBrick;
    InsertBrick *insertBrick;
    AlignBrick *alignBrick;
    QMdiArea *mdiArea;              // Replacing single DocumentWindow
    DocumentHandlerBrick *documentHandler;
};

#endif // MAINWINDOWBRICK_H
