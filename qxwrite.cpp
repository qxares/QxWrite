#include "qxwrite.h"
#include <QMenuBar>
#include <QDebug>
#include "generalmanagerbrick.h"

QxWrite::QxWrite(QWidget *parent)
    : QMainWindow(parent),
      textEdit(new QTextEdit(this)),
      manager(new GeneralManagerBrick(this)) {
    qDebug() << "QxWrite starting...";
    textEdit->setAcceptRichText(true);
    setCentralWidget(textEdit);
    manager->initBricks();
    qDebug() << "QxWrite ready.";
}

QxWrite::~QxWrite() {}

