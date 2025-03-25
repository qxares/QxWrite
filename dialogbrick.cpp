#include "dialogbrick.h"
#include <QFileDialog>
#include <QDir>
#include <QDebug>

DialogBrick::DialogBrick(QObject *parent) : QObject(parent) {
    lastDir = QDir::homePath();
    qDebug() << "DialogBrick initialized with lastDir:" << lastDir;
}

QString DialogBrick::getOpenFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter) {
    QString useDir = dir.isEmpty() ? lastDir : dir;
    qDebug() << "DialogBrick: getOpenFileName called with parent:" << parent << "caption:" << caption << "dir:" << useDir << "filter:" << filter;

    QString fileName = QFileDialog::getOpenFileName(parent, caption, useDir, filter);
    qDebug() << "DialogBrick: QFileDialog returned:" << fileName;

    if (!fileName.isEmpty()) {
        lastDir = QFileInfo(fileName).absolutePath();
        qDebug() << "DialogBrick: Updated lastDir to:" << lastDir;
    } else {
        qDebug() << "DialogBrick: Open cancelled";
        QDir dir(useDir);
        QStringList contents = dir.entryList(QDir::AllEntries | QDir::NoDot);
        qDebug() << "DialogBrick: File view (left pane) contents in" << useDir << ":" << contents;
    }

    return fileName;
}

QString DialogBrick::getSaveFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter) {
    QString useDir = dir.isEmpty() ? lastDir : dir;
    QString fileName = QFileDialog::getSaveFileName(parent, caption, useDir, filter);
    if (!fileName.isEmpty()) {
        lastDir = QFileInfo(fileName).absolutePath();
    }
    return fileName;
}
