#include "documentwindow.h"
#include "newfilebrick.h"
#include "openfilebrick.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QDebug>
#include <QMdiSubWindow>
#include <QMenu>

DocumentWindow::DocumentWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    textEdit = new QTextEdit(this);
    textEdit->setFrameStyle(QFrame::NoFrame);  // Clean look like a word processor
    textEdit->setAcceptRichText(true);         // Enable rich text for formatting
    layout->addWidget(textEdit);
    setLayout(layout);

    newFileBrick = new NewFileBrick(textEdit, this);
    openFileBrick = new OpenFileBrick(textEdit, this);

    // Enable custom context menu on the subwindow (set by parent later)
    if (QMdiSubWindow *subWindow = qobject_cast<QMdiSubWindow*>(this->parent())) {
        subWindow->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(subWindow, &QMdiSubWindow::customContextMenuRequested, this, [this, subWindow](const QPoint &pos) {
            emit customContextMenuRequested(subWindow, pos);
        });
    }

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
        doc->setDefaultFont(QFont("Times New Roman", 12));  // Default word processor feel
        qDebug() << "DocumentWindow: New QxDocument created";
    } else {
        newFileBrick->newFile(type);
        qDebug() << "DocumentWindow: New file created, type:" << type;
    }
}
