#include "documentwindow.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QDebug>
#include "imagescenemanager.h"

DocumentWindow::DocumentWindow(ImageSceneManager *sceneManager, QWidget *parent)
    : QWidget(parent), m_sceneManager(sceneManager) {
    qDebug() << "Creating DocumentWindow...";
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_textEdit = new QTextEdit(this);
    m_textEdit->setAcceptRichText(true);
    qDebug() << "Rich text enabled:" << m_textEdit->acceptRichText();
    layout->addWidget(m_textEdit);
    setLayout(layout);
    qDebug() << "Editor created:" << true;
}

QTextEdit* DocumentWindow::getTextEdit() {
    return m_textEdit;
}
