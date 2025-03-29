#include "mainwindowbrick.h"
#include <QTextEdit>
#include <QDebug>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>
#include "boldbrick.h"
#include "italicbrick.h"
#include "savefunctionbrick.h"
#include "savehandlerbrick.h"
#include "saveguibrick.h"
#include "savemanagerbrick.h"
#include "placeholderbrick.h"

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "MainWindowBrick starting...";
    
    // Central widget with layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    edit = new QTextEdit(centralWidget); // Parent to centralWidget
    edit->setMinimumSize(600, 400);
    layout->addWidget(edit);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    
    resize(800, 600);
    setWindowTitle("QxWrite");

    // Force visibility and debug
    edit->setVisible(true);
    centralWidget->setVisible(true);
    qDebug() << "QTextEdit created at:" << edit << "Visible:" << edit->isVisible();
    qDebug() << "CentralWidget visible:" << centralWidget->isVisible() << "Size:" << centralWidget->size();
    qDebug() << "Layout contains QTextEdit:" << (layout->indexOf(edit) != -1);

    // Toolbar Setup
    QToolBar *toolbar = addToolBar("Tools");
    toolbar->setMovable(false);

    // Bold Action
    BoldBrick *boldBrick = new BoldBrick(edit, this);
    toolbar->addAction("Bold", boldBrick, &BoldBrick::applyBold);

    // Italic Action
    ItalicBrick *italicBrick = new ItalicBrick(edit, this);
    toolbar->addAction("Italic", italicBrick, &ItalicBrick::applyItalic);

    // Save Action
    SaveFunctionBrick *saveFunction = new SaveFunctionBrick(edit, this);
    SaveGUIBrick *saveGui = new SaveGUIBrick(edit, this);
    SaveHandlerBrick *saveHandler = new SaveHandlerBrick(saveFunction, saveGui, this);
    SaveManagerBrick *saveManager = new SaveManagerBrick(edit, this);
    toolbar->addAction("Save", saveManager, &SaveManagerBrick::triggerSave);

    // Placeholder Context Menu
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &MainWindowBrick::customContextMenuRequested, this, [this](const QPoint &pos) {
        PlaceholderBrick *placeholderBrick = new PlaceholderBrick(edit, this);
        placeholderBrick->insertPlaceholder(edit->textCursor().position(), PlaceholderBrick::Table);
    });

    // Connections
    connect(saveHandler, &SaveHandlerBrick::completed, saveManager, &SaveManagerBrick::validate);

    // Force layout update and repaint
    layout->activate();
    centralWidget->update();
    edit->repaint();
    show();
    qDebug() << "After show - QTextEdit visible:" << edit->isVisible() << "Geometry:" << edit->geometry();
    qDebug() << "After show - CentralWidget visible:" << centralWidget->isVisible() << "Geometry:" << centralWidget->geometry();
    qDebug() << "MainWindow visible:" << isVisible() << "Geometry:" << geometry();

    qDebug() << "MainWindowBrick ready.";
}

MainWindowBrick::~MainWindowBrick() {
    // Cleanup if needed
}

void MainWindowBrick::handleOpenFile() {
    qDebug() << "Open file triggered (stub)";
}
