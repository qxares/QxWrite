#include "documentwindow.h"
#include "newfilebrick.h"
#include "openfilebrick.h"
#include "saveguibrick.h"
#include "savefunctionbrick.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QDebug>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QCloseEvent>

DocumentWindow::DocumentWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    textEdit = new QTextEdit(this);
    textEdit->setFrameStyle(QFrame::NoFrame);
    textEdit->setAcceptRichText(true);
    layout->addWidget(textEdit);
    setLayout(layout);

    newFileBrick = new NewFileBrick(textEdit, this);
    openFileBrick = new OpenFileBrick(textEdit, this);
    saveGuiBrick = new SaveGUIBrick(textEdit, this);
    saveFunctionBrick = new SaveFunctionBrick(textEdit, this);

    qDebug() << "DocumentWindow initialized with textEdit:" << textEdit;
}

DocumentWindow::~DocumentWindow() {
    delete newFileBrick;
    qDebug() << "DocumentWindow: NewFileBrick destroyed";
    delete openFileBrick;
    qDebug() << "DocumentWindow: OpenFileBrick destroyed";
    delete saveGuiBrick;
    qDebug() << "DocumentWindow: SaveGUIBrick destroyed";
    delete saveFunctionBrick;
    qDebug() << "DocumentWindow: SaveFunctionBrick destroyed";
    delete textEdit;
    qDebug() << "DocumentWindow: TextEdit destroyed";
    qDebug() << "DocumentWindow destroyed";
}

QTextEdit* DocumentWindow::getTextEdit() const {
    return textEdit;
}

void DocumentWindow::clear() {
    textEdit->clear();
    qDebug() << "DocumentWindow cleared";
}

void DocumentWindow::newFile(NewFileBrick::DocType type) {
    clear();
    newFileBrick->newFile(type);
    qDebug() << "DocumentWindow: New file created, type:" << static_cast<int>(type);
}

void DocumentWindow::closeEvent(QCloseEvent *event) {
    if (textEdit->document()->isModified()) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Save Changes?",
            "Do you want to save changes to this document before closing?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
        );
        if (reply == QMessageBox::Yes) {
            QString fileName = saveGuiBrick->getSaveFileName(true);
            if (!fileName.isEmpty()) {
                saveFunctionBrick->save(fileName);
                event->accept();
            } else {
                event->ignore();
            }
        } else if (reply == QMessageBox::No) {
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        event->accept();
    }
}
