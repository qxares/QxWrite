#ifndef MAINWINDOWBRICK_H
#define MAINWINDOWBRICK_H

#include <QMainWindow>

class QMdiArea;
class ToolBarBrick;
class MenuManagerBrick;
class NewFileBrick;
class OpenFileBrick;
class ImportBrick;
class ExportBrick;
class SaveManagerBrick;
class BoldBrick;
class ItalicBrick;
class FontBrick;
class ColorBrick;
class InsertBrick;
class AlignBrick;
class DocumentHandlerBrick;
class ResizeBrick;
class TranslatorBrick;
class TableBrick;
class ListBrick;

class MainWindowBrick : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindowBrick(QWidget *parent = nullptr);
    ~MainWindowBrick();

private slots:
    void handleOpenFile();
    void handleImportFile();
    void handleExportFile();
    void exitApplication();
    void showAboutDialog();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QMdiArea *mdiArea;
    ToolBarBrick *toolBarBrick;
    MenuManagerBrick *menuManagerBrick;
    BoldBrick *boldBrick;
    ImportBrick *importBrick;
    ExportBrick *exportBrick;
    TranslatorBrick *translatorBrick;
    TableBrick *tableBrick;
    ListBrick *listBrick;
    DocumentHandlerBrick *documentHandler;
};

#endif // MAINWINDOWBRICK_H
