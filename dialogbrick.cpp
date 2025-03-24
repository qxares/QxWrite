#include "dialogbrick.h"
#include <QFileDialog>
#include <QDebug>

DialogBrick::DialogBrick(QObject *parent) : QObject(parent) {
    qDebug() << "DialogBrick initialized";
}

QString DialogBrick::getSaveFileName(const QString &caption, const QString &dir, const QString &filter) {
    QString defaultFilter = "Markdown Files (*.md)";
    QString selectedFile = QFileDialog::getSaveFileName(nullptr, caption, dir, "Markdown Files (*.md);;Text Files (*.txt);;HTML Files (*.html)", &defaultFilter, QFileDialog::DontUseNativeDialog);
    if (selectedFile.isEmpty()) return "";
    if (!selectedFile.endsWith(".md") && !selectedFile.endsWith(".txt") && !selectedFile.endsWith(".html")) {
        selectedFile += ".md"; // Default to .md if no extension
    }
    qDebug() << "DialogBrick: Save selected:" << selectedFile;
    return selectedFile;
}

QString DialogBrick::getOpenFileName(const QString &caption, const QString &dir, const QString &filter) {
    QString defaultFilter = "Markdown Files (*.md)";
    QString selectedFile = QFileDialog::getOpenFileName(nullptr, caption, dir, "Markdown Files (*.md);;Text Files (*.txt);;HTML Files (*.html)", &defaultFilter, QFileDialog::DontUseNativeDialog);
    qDebug() << "DialogBrick: Open selected:" << selectedFile;
    return selectedFile;
}

