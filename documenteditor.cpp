#include "documenteditor.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QGraphicsView>
#include "imagedraghandler.h"

DocumentEditor::DocumentEditor(ImageSceneManager *sceneManager, QWidget *parent)
    : QWidget(parent), sceneManager(sceneManager) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    textEdit = new QTextEdit(this);
    view = new QGraphicsView(sceneManager->scene(), this);
    textEdit->setViewport(view->viewport());  // Overlay graphics on text
    layout->addWidget(textEdit);
    setLayout(layout);

    ImageDragHandler *dragHandler = new ImageDragHandler(sceneManager, this);
    view->installEventFilter(dragHandler);
}

bool DocumentEditor::acceptRichText() const {
    return textEdit->acceptRichText();
}

QTextEdit* DocumentEditor::getTextEdit() const {
    return textEdit;
}
