#include "documentwindow.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include "openfilebrick.h"

DocumentWindow::DocumentWindow(ImageSceneManager *sceneManager, QWidget *parent)
    : QWidget(parent), sceneManager(sceneManager) { // Updated constructor
    textEdit = new QTextEdit(this);
    newFileBrick = new NewFileBrick(textEdit, this); // Pass textEdit instead of this
    openFileBrick = new OpenFileBrick(textEdit, this); // Pass textEdit instead of this

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(textEdit);
    setLayout(layout);

    textEdit->installEventFilter(this);
}

DocumentWindow::~DocumentWindow() {}

QTextEdit* DocumentWindow::getTextEdit() const {
    return textEdit;
}

void DocumentWindow::clear() {
    textEdit->clear();
}

void DocumentWindow::newFile(NewFileBrick::DocType type) {
    clear();
    // Add type-specific initialization later if needed
}

bool DocumentWindow::eventFilter(QObject *obj, QEvent *event) {
    return QWidget::eventFilter(obj, event);
}
