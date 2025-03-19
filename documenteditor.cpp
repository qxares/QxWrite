#include "documenteditor.h"
#include <QDebug>
#include <QTextCursor>
#include <QFont>

DocumentEditor::DocumentEditor(QWidget *parent) : QTextEdit(parent), selector(this) {
    setAcceptRichText(true);
    setDocumentTitle("Untitled Document");
    document()->setDefaultFont(QFont("Times New Roman", 12));
    sceneManager = new ImageSceneManager(this);
    resizer = new ImageResizer(this);
    mouseHandler = new MouseEventHandler(sceneManager, resizer, this);
    dragHandler = new ImageDragHandler(sceneManager, this);
    contextHandler = new ContextMenuHandler(sceneManager, resizer, &selector, this);
    sceneManager->setGeometry(rect());
    resizer->setGeometry(rect());
    sceneManager->installEventFilter(dragHandler);
    sceneManager->installEventFilter(mouseHandler);
    setContextMenuPolicy(Qt::CustomContextMenu); // Disable default menu
    qDebug() << "Rich text enabled:" << acceptRichText();
}

DocumentEditor::~DocumentEditor() {
    delete sceneManager;
    delete resizer;
    delete mouseHandler;
    delete dragHandler;
    delete contextHandler;
}

void DocumentEditor::contextMenuEvent(QContextMenuEvent *event) {
    contextHandler->showContextMenu(event);
    event->accept(); // Ensure event doesn’t propagate to default handler
}

void DocumentEditor::resizeEvent(QResizeEvent *event) {
    QTextEdit::resizeEvent(event);
    sceneManager->setGeometry(rect());
    resizer->setGeometry(rect());
}
