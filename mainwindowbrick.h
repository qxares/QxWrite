#ifndef MAINWINDOWBRICK_H
#define MAINWINDOWBRICK_H

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
class ListBrick;  // New brick
class DocumentHandlerBrick;

class MainWindowBrick : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindowBrick(QWidget *parent = nullptr);
    ~MainWindowBrick();

private slots:
    void handleOpenFile();

private:
    QMdiArea *mdiArea;
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
    ListBrick *listBrick;  // New brick
    DocumentHandlerBrick *documentHandler;
};

#endif // MAINWINDOWBRICK_H
