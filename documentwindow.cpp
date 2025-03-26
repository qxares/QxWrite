#include "documentwindow.h"
#include "newfilebrick.h"
#include "openfilebrick.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QDebug>

DocumentWindow::DocumentWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    textEdit = new QTextEdit(this);
    layout->addWidget(textEdit);
    setLayout(layout);

    newFileBrick = new NewFileBrick(textEdit, this);
    openFileBrick = new OpenFileBrick(textEdit, this);

    qDebug() << "DocumentWindow initialized with textEdit:" << textEdit;
}

DocumentWindow::~DocumentWindow() {
    delete newFileBrick;
    delete openFileBrick;
    delete textEdit;
}

QTextEdit* DocumentWindow::getTextEdit() const {
    return textEdit;
}

void DocumentWindow::clear() {
    textEdit->clear();
    qDebug() << "DocumentWindow cleared";
}

void DocumentWindow::newFile(NewFileBrick::DocType type) {
    newFileBrick->newFile(type);
    qDebug() << "DocumentWindow: New file created, type:" << type;
}
