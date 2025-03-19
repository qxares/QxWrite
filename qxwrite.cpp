#include "qxwrite.h"
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QDebug>
#include <QTimer>
#include "menumanager.h"
#include "filemanager.h"
#include "documentwindow.h"
#include "imageplaceholderinserter.h"
#include "imagemanipulator.h"

QxWrite::QxWrite(QWidget *parent) 
    : QMainWindow(parent), 
      mdiArea(new QMdiArea(this)), 
      sceneManager(new ImageSceneManager(this)), 
      menuManager(new MenuManager(menuBar(), this)),
      fileManager(new FileManager(this)),
      inserter(new ImagePlaceholderInserter(sceneManager, this)), 
      resizer(new ImageResizer(this)),
      manipulator(nullptr),
      selector(nullptr) {
    qDebug() << "QxWrite constructor starting...";
    setCentralWidget(mdiArea);
    qDebug() << "MDI area created successfully.";
    qDebug() << "ImageSceneManager initialized";
    resizer->setSceneManager(sceneManager);

    menuManager->addFileMenu();
    QList<QAction*> imageActions;
    QAction *insertAction = new QAction(tr("Insert Image"), this);
    insertAction->setObjectName("insertImage");
    imageActions.append(insertAction);
    moveAction = new QAction(tr("Move Image"), this);
    moveAction->setObjectName("moveImage");
    imageActions.append(moveAction);
    resizeAction = new QAction(tr("Resize Image"), this);
    resizeAction->setObjectName("resizeImage");
    imageActions.append(resizeAction);
    connect(insertAction, &QAction::triggered, this, &QxWrite::insertImageToActiveEditor);
    menuManager->addCustomMenu(tr("&Image"), imageActions);

    connect(menuManager, &MenuManager::newFileRequested, this, &QxWrite::handleNewFile);
    connect(menuManager, &MenuManager::openFileRequested, this, &QxWrite::handleOpenFile);
    connect(menuManager, &MenuManager::saveFileRequested, this, &QxWrite::handleSaveFile);
    connect(menuManager, &MenuManager::quitRequested, this, &QxWrite::close);
    
    qDebug() << "QxWrite constructor finished.";
    QTimer::singleShot(0, this, [this]() { qDebug() << "Menu bar visible after delay:" << menuBar()->isVisible(); });
}

void QxWrite::handleNewFile() {
    qDebug() << "Handling new file request...";
    DocumentWindow *editor = new DocumentWindow(sceneManager, this);
    qDebug() << "Editor created:" << (editor != nullptr);
    if (editor) {
        handleEditorCreated(editor);
    } else {
        qDebug() << "Failed to create editor!";
    }
}

void QxWrite::handleOpenFile() { fileManager->openFile(); }
void QxWrite::handleSaveFile() { fileManager->saveFile(); }

void QxWrite::handleEditorCreated(DocumentWindow *editor) {
    qDebug() << "Adding editor to MDI...";
    mdiArea->addSubWindow(editor);
    qDebug() << "Showing editor...";
    editor->show();
    qDebug() << "Editor shown, getting text edit...";
    QTextEdit *textEdit = editor->getTextEdit();
    qDebug() << "Text edit retrieved:" << (textEdit != nullptr);

    if (textEdit) {
        qDebug() << "Creating selector...";
        selector = new ImageSelector(textEdit, this);
        selector->setSceneManager(sceneManager);
        qDebug() << "Selector created, creating manipulator...";
        manipulator = new ImageManipulator(sceneManager, resizer, selector, this);
        qDebug() << "Manipulator created";
        
        QList<QAction*> imageActions;
        QAction *insertAction = new QAction(tr("Insert Image"), this);
        insertAction->setObjectName("insertImage");
        imageActions.append(insertAction);
        imageActions.append(moveAction);
        imageActions.append(resizeAction);
        disconnect(moveAction, nullptr, nullptr, nullptr);
        disconnect(resizeAction, nullptr, nullptr, nullptr);
        connect(insertAction, &QAction::triggered, this, &QxWrite::insertImageToActiveEditor);
        connect(moveAction, &QAction::triggered, manipulator, &ImageManipulator::moveImage);
        connect(resizeAction, &QAction::triggered, manipulator, &ImageManipulator::resizeImage);
        menuManager->addCustomMenu(tr("&Image"), imageActions);
        qDebug() << "Updated image menu actions";
    } else {
        qDebug() << "Text edit is null, skipping selector/manipulator setup";
    }
}

void QxWrite::insertImageToActiveEditor() {
    qDebug() << "Insert image to active editor triggered";
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    if (!activeSubWindow) {
        qDebug() << "No active subwindow!";
        return;
    }
    DocumentWindow *docWindow = qobject_cast<DocumentWindow*>(activeSubWindow->widget());
    if (!docWindow) {
        qDebug() << "Active subwindow is not a DocumentWindow!";
        return;
    }
    inserter->insertImage(docWindow);
}

QxWrite::~QxWrite() {}

