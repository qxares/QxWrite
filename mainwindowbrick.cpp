#include "mainwindowbrick.h"
#include "toolbarbrick.h"
#include "menumanagerbrick.h"
#include "newfilebrick.h"
#include "openfilebrick.h"
#include "importbrick.h"
#include "exportbrick.h"
#include "savemanagerbrick.h"
#include "boldbrick.h"
#include "italicbrick.h"
#include "fontbrick.h"
#include "colorbrick.h"
#include "insertbrick.h"
#include "alignbrick.h"
//#include "listbrick.h"
//#include "tablebrick.h"
//#include "tablehandlerbrick.h"
#include "documenthandlerbrick.h"
#include "resizebrick.h"
#include "translatorbrick.h"
#include <QMdiArea>
#include <QMenu>
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QWidgetAction>  // Added for source language QComboBox in menu
#include <QGraphicsDropShadowEffect>  // For shadow effect

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

    documentHandler = new DocumentHandlerBrick(this);
    toolBarBrick = new ToolBarBrick(this);
    menuManagerBrick = new MenuManagerBrick(this);
    boldBrick = new BoldBrick(nullptr, documentHandler);
    importBrick = new ImportBrick(nullptr, this);
    exportBrick = new ExportBrick(nullptr, this);
    translatorBrick = new TranslatorBrick(nullptr, this);

    addToolBar(toolBarBrick->getToolBar());
    setMenuBar(menuManagerBrick->getMenuBar());

    resize(800, 600);

    QAction *openAction = toolBarBrick->getAction("open");
    QAction *saveAction = toolBarBrick->getAction("save");
    QAction *boldAction = toolBarBrick->getAction("bold");
    QAction *italicAction = toolBarBrick->getAction("italic");
    QAction *fontAction = toolBarBrick->getAction("font");
    QAction *colorAction = toolBarBrick->getAction("color");
    QAction *imageAction = toolBarBrick->getAction("image");
    QAction *alignLeftAction = toolBarBrick->getAction("alignLeft");
    QAction *alignCenterAction = toolBarBrick->getAction("alignCenter");
    QAction *alignRightAction = toolBarBrick->getAction("alignRight");
    QAction *translateAction = new QAction("Translate", this);
    translateAction->setData(QVariant::fromValue(translatorBrick->getTargetLanguageComboBox()));  // Attach target combo

    menuManagerBrick->setupMenus(openAction, saveAction, boldAction, italicAction, fontAction,
                                 colorAction, imageAction, alignLeftAction, alignCenterAction,
                                 alignRightAction, nullptr, translateAction);  // Removed nullptrs for numberingAction and bulletsAction

    // Add source language submenu under Tools with reset action
    QMenu *toolsMenu = menuManagerBrick->getMenuBar()->findChild<QMenu*>("Tools");
    if (toolsMenu) {
        QMenu *sourceMenu = toolsMenu->addMenu("Translate From");
        sourceMenu->addAction(QAction::tr("Source Language"))->setEnabled(false);  // Placeholder label
        sourceMenu->addSeparator();
        QWidgetAction *sourceWidgetAction = new QWidgetAction(this);
        sourceWidgetAction->setDefaultWidget(translatorBrick->getSourceLanguageComboBox());
        sourceMenu->addAction(sourceWidgetAction);
        QAction *resetAction = sourceMenu->addAction("Reset");
        connect(resetAction, &QAction::triggered, translatorBrick, &TranslatorBrick::resetTranslation);
    }

    connect(boldAction, &QAction::triggered, boldBrick, &BoldBrick::applyBold);
    connect(menuManagerBrick, &MenuManagerBrick::importTriggered, this, &MainWindowBrick::handleImportFile);
    connect(menuManagerBrick, &MenuManagerBrick::exportTriggered, exportBrick, &ExportBrick::exportFile);
    connect(menuManagerBrick, &MenuManagerBrick::translateTriggered, translatorBrick, &TranslatorBrick::translateText);
    connect(menuManagerBrick, &MenuManagerBrick::aboutTriggered, this, &MainWindowBrick::showAboutDialog);

    connect(mdiArea, &QMdiArea::subWindowActivated, this, [this]() {
        QTextEdit *activeEdit = documentHandler->getActiveTextEdit();
        boldBrick->setTextEdit(activeEdit);
        importBrick->setTextEdit(activeEdit);
        exportBrick->setTextEdit(activeEdit);
        translatorBrick->setTextEdit(activeEdit);
        qDebug() << "MainWindowBrick: BoldBrick synced with active textEdit:" << activeEdit;
    });

    connect(menuManagerBrick, &MenuManagerBrick::newFileTriggered, this, [this, openAction, saveAction, italicAction, fontAction, colorAction, imageAction, alignLeftAction, alignCenterAction, alignRightAction](int type) {
        QTextEdit *textEdit = documentHandler->newDocument(static_cast<NewFileBrick::DocType>(type));
        if (!textEdit) return;

        auto *openFileBrick = new OpenFileBrick(textEdit, this);
        auto *saveManagerBrick = new SaveManagerBrick(textEdit, this);
        auto *italicBrick = new ItalicBrick(textEdit, this);
        auto *fontBrick = new FontBrick(textEdit, this);
        auto *colorBrick = new ColorBrick(textEdit, this);
        auto *insertBrick = new InsertBrick(textEdit, this);
        auto *alignBrick = new AlignBrick(textEdit, this);
        auto *resizeBrick = new ResizeBrick(textEdit, this);
        resizeBrick->enableResize();

        connect(openAction, &QAction::triggered, openFileBrick, &OpenFileBrick::openFile);
        connect(saveAction, &QAction::triggered, saveManagerBrick, &SaveManagerBrick::triggerSave);
        connect(italicAction, &QAction::triggered, italicBrick, &ItalicBrick::applyItalic);
        connect(fontAction, &QAction::triggered, fontBrick, &FontBrick::changeFont);
        connect(colorAction, &QAction::triggered, colorBrick, &ColorBrick::changeColor);
        connect(imageAction, &QAction::triggered, insertBrick, &InsertBrick::insertImage);
        connect(alignLeftAction, &QAction::triggered, alignBrick, [alignBrick]() { alignBrick->align(Qt::AlignLeft); });
        connect(alignCenterAction, &QAction::triggered, alignBrick, [alignBrick]() { alignBrick->align(Qt::AlignCenter); });
        connect(alignRightAction, &QAction::triggered, alignBrick, [alignBrick]() { alignBrick->align(Qt::AlignRight); });

        connect(menuManagerBrick, &MenuManagerBrick::saveAsTriggered, saveManagerBrick, &SaveManagerBrick::triggerSaveAs);
        connect(menuManagerBrick, &MenuManagerBrick::moveTriggered, resizeBrick, &ResizeBrick::moveObject);

        QMenu *tableMenu = menuManagerBrick->getMenuBar()->findChild<QMenu*>("Table");
        if (tableMenu) {
            tableMenu->addAction("Move", [resizeBrick]() { resizeBrick->moveObject(); });
        }

        connect(mdiArea, &QMdiArea::subWindowActivated, this, [this, textEdit]() {
            if (mdiArea->activeSubWindow() && mdiArea->activeSubWindow()->widget()) {
                QTextEdit *activeEdit = qobject_cast<DocumentWindow*>(mdiArea->activeSubWindow()->widget())->getTextEdit();
                if (activeEdit == textEdit) {
                    // No tableHandlerBrick to set
                }
            }
        });

        QMdiSubWindow *subWindow = mdiArea->activeSubWindow();
        if (subWindow) {
            connect(subWindow, &QMdiSubWindow::destroyed, boldBrick, &BoldBrick::resetTextEdit);
        }
    });

    connect(openAction, &QAction::triggered, this, &MainWindowBrick::handleOpenFile);
    connect(menuManagerBrick, &MenuManagerBrick::exitTriggered, this, &MainWindowBrick::exitApplication);

    QMenu *fileMenu = menuManagerBrick->getMenuBar()->findChild<QMenu*>("File");
    if (fileMenu) {
        qDebug() << "File menu actions:" << fileMenu->actions().count();
        for (QAction *action : fileMenu->actions()) {
            qDebug() << "File menu item:" << action->text();
        }
    }

    qDebug() << "MainWindowBrick ready.";
}

MainWindowBrick::~MainWindowBrick() {
    delete boldBrick;
    qDebug() << "MainWindowBrick: BoldBrick destroyed";
    delete importBrick;
    qDebug() << "MainWindowBrick: ImportBrick destroyed";
    delete exportBrick;
    qDebug() << "MainWindowBrick: ExportBrick destroyed";
    delete translatorBrick;
    qDebug() << "MainWindowBrick: TranslatorBrick destroyed";
    delete documentHandler;
    qDebug() << "MainWindowBrick: DocumentHandlerBrick destroyed";
    delete toolBarBrick;
    qDebug() << "MainWindowBrick: ToolBarBrick destroyed";
    delete menuManagerBrick;
    qDebug() << "MainWindowBrick: MenuManagerBrick destroyed";
    delete mdiArea;
    qDebug() << "MainWindowBrick: MDIArea destroyed";
    qDebug() << "MainWindowBrick destroyed";
}

void MainWindowBrick::handleOpenFile() {
    documentHandler->openDocument(new OpenFileBrick(nullptr, this));
}

void MainWindowBrick::handleImportFile() {
    QTextEdit *activeEdit = documentHandler->getActiveTextEdit();
    if (!activeEdit) {
        activeEdit = documentHandler->newDocument(NewFileBrick::DocType::Document);
        if (!activeEdit) return;
    }
    importBrick->setTextEdit(activeEdit);
    importBrick->importFile();
}

void MainWindowBrick::handleExportFile() {
    QTextEdit *activeEdit = documentHandler->getActiveTextEdit();
    if (activeEdit) {
        ExportBrick *exportBrick = new ExportBrick(activeEdit, this);
        exportBrick->exportFile();
    }
}

void MainWindowBrick::exitApplication() {
    qDebug() << "MainWindowBrick: Exit triggered, closing application.";
    close();
}

void MainWindowBrick::closeEvent(QCloseEvent *event) {
    QList<QMdiSubWindow*> subWindows = mdiArea->subWindowList();
    for (QMdiSubWindow *subWindow : subWindows) {
        DocumentWindow *docWindow = qobject_cast<DocumentWindow*>(subWindow->widget());
        if (docWindow && docWindow->getTextEdit() && docWindow->getTextEdit()->document()->isModified()) {
            subWindow->show();
            QMessageBox::StandardButton reply = QMessageBox::question(
                this, "Unsaved Changes",
                QString("Save changes to %1 before closing?").arg(subWindow->windowTitle()),
                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
            );
            if (reply == QMessageBox::Yes) {
                QMdiSubWindow *currentSubWindow = mdiArea->currentSubWindow();
                mdiArea->setActiveSubWindow(subWindow);
                SaveManagerBrick *saveManager = nullptr;
                for (QObject *child : subWindow->widget()->children()) {
                    saveManager = qobject_cast<SaveManagerBrick*>(child);
                    if (saveManager) break;
                }
                if (!saveManager) {
                    saveManager = new SaveManagerBrick(docWindow->getTextEdit(), this);
                }
                if (!saveManager->triggerSave()) {
                    event->ignore();
                    if (currentSubWindow) mdiArea->setActiveSubWindow(currentSubWindow);
                    return;
                }
                if (currentSubWindow) mdiArea->setActiveSubWindow(currentSubWindow);
            } else if (reply == QMessageBox::Cancel) {
                event->ignore();
                return;
            }
        }
    }
    for (QMdiSubWindow *subWindow : subWindows) {
        subWindow->close();
    }
    qDebug() << "MainWindowBrick: All subwindows closed, accepting close event.";
    event->accept();
}

void MainWindowBrick::showAboutDialog() {
    QMessageBox *aboutBox = new QMessageBox(this);
    aboutBox->setWindowTitle("About QxWrite");
    aboutBox->setText("QxWrite - Created by Mac & Grok, xAI");
    aboutBox->setStandardButtons(QMessageBox::Ok);

    // Apply shadow effect
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(15);
    shadowEffect->setXOffset(5);
    shadowEffect->setYOffset(5);
    QColor shadowColor(0, 0, 255, 180);  // Blue shadow with same intensity as green (180 alpha)
    shadowEffect->setColor(shadowColor);
    qDebug() << "MainWindowBrick: Applying shadow color (R,G,B,A):" << shadowColor.red() << shadowColor.green() << shadowColor.blue() << shadowColor.alpha();
    aboutBox->setGraphicsEffect(shadowEffect);

    aboutBox->exec();
    delete aboutBox;  // Clean up to avoid memory leak
}
