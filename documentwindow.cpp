#include "documentwindow.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QDebug>
#include "imagescenemanager.h"

DocumentWindow::DocumentWindow(ImageSceneManager *sceneManager, QWidget *parent)
    : QMainWindow(parent), textEdit(new QTextEdit(this)) {
    qDebug() << "Creating DocumentWindow...";
    textEdit->setAcceptRichText(true);
    qDebug() << "Rich text enabled:" << textEdit->acceptRichText();
    setCentralWidget(textEdit);
    qDebug() << "Editor created:" << true;
}
