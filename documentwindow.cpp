#include "documentwindow.h"
#include "newfilebrick.h"
#include "openfilebrick.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QDebug>
#include <QMdiSubWindow>
#include <QEvent>

DocumentWindow::DocumentWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    textEdit = new QTextEdit(this);
    textEdit->setFrameStyle(QFrame::NoFrame);
    textEdit->setAcceptRichText(true);
    textEdit->installEventFilter(this);
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
    clear();
    if (type == NewFileBrick::Document) {
        textEdit->setDocumentTitle("Untitled Document");
        QTextDocument *doc = textEdit->document();
        doc->setDefaultFont(QFont("Times New Roman", 12));
        qDebug() << "DocumentWindow: New QxDocument created";
    } else {
        newFileBrick->newFile(type);
        qDebug() << "DocumentWindow: New file created, type:" << type;
    }
}

bool DocumentWindow::eventFilter(QObject *obj, QEvent *event) {
    if (obj == textEdit) {
        if (event->type() == QEvent::MouseButtonPress ||
            event->type() == QEvent::MouseMove ||
            event->type() == QEvent::MouseButtonRelease) {
            return false; // Let QTextEdit handle selection
        }
    }
    return QWidget::eventFilter(obj, event);
}
