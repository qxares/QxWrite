#ifndef MAINWINDOWBRICK_H
#define MAINWINDOWBRICK_H

#include <QMainWindow>
#include <QMdiArea>

class ToolBarBrick;
class MenuManagerBrick;
class DocumentHandlerBrick;
class TableHandlerBrick;

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
    DocumentHandlerBrick *documentHandler;
    TableHandlerBrick *activeTableHandler; // Tracks active document's TableHandlerBrick
};

#endif // MAINWINDOWBRICK_H
