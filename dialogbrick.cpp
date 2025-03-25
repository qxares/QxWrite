#include "dialogbrick.h"
#include <QFileDialog>
#include <QDebug>
#include <QDir>

DialogBrick::DialogBrick(QObject *parent) : QObject(parent) {
    lastDir = QDir::homePath();
    qDebug() << "DialogBrick initialized with lastDir:" << lastDir;
}

QString DialogBrick::getOpenFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter) {
    QString useDir = dir.isEmpty() ? lastDir : dir;
    QString fileName = QFileDialog::getOpenFileName(parent, caption, useDir, filter);
    if (!fileName.isEmpty()) {
        lastDir = QFileInfo(fileName).absolutePath();
        qDebug() << "DialogBrick: Selected file:" << fileName;
    } else {
        qDebug() << "DialogBrick: Open cancelled";
    }
    QDir dirView(useDir);
    qDebug() << "DialogBrick: File view (left pane) contents in" << useDir << ":" << dirView.entryList(QDir::AllEntries | QDir::NoDot);
    return fileName;
}
