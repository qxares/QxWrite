#ifndef MAINWINDOWBRICK_H
#define MAINWINDOWBRICK_H

#include <QMainWindow>
#include "documenthandlerbrick.h"
#include "toolbarbrick.h"
#include "menumanagerbrick.h"
#include "boldbrick.h"
#include "importbrick.h"  // Add for ImportBrick
#include "exportbrick.h"  // Add for ExportBrick
#include "translatorbrick.h"  // Added for TranslatorBrick

class QMdiArea;

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
    void showAboutDialog();  // Added for Help -> About

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QMdiArea *mdiArea;
    DocumentHandlerBrick *documentHandler;
    ToolBarBrick *toolBarBrick;
    MenuManagerBrick *menuManagerBrick;
    BoldBrick *boldBrick;
    ImportBrick *importBrick;  // Declare global instance
    ExportBrick *exportBrick;  // Declare global instance
    TranslatorBrick *translatorBrick;  // Added global instance
};

#endif // MAINWINDOWBRICK_H
