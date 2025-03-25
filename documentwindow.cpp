#include "documentwindow.h"
#include "openfilebrick.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QDebug>

DocumentWindow::DocumentWindow(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "DocumentWindow: Initializing...";
    setupUI();
    qDebug() << "DocumentWindow: Ready.";
}

void DocumentWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    textEdit = new QTextEdit(this);
    layout->addWidget(textEdit);
    
    openFileBrick = new OpenFileBrick(textEdit, this);
    
    setCentralWidget(centralWidget);
    resize(600, 400);
}
