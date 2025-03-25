#include "dialogbrick.h"
#include <QFileDialog>
#include <QDebug>

DialogBrick::DialogBrick(QObject *parent) : QObject(parent) {
    lastDir = QDir::homePath();
    qDebug() << "DialogBrick initialized with lastDir:" << lastDir;
}

QString DialogBrick::getOpenFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter) {
    qDebug() << "DialogBrick: getOpenFileName called, parent:" << parent << ", caption:" << caption << ", dir:" << dir << ", filter:" << filter;
    QString selectedFile = QFileDialog::getOpenFileName(parent, caption, dir.isEmpty() ? lastDir : dir, filter);
    if (!selectedFile.isEmpty()) {
        lastDir = QFileInfo(selectedFile).absolutePath();
        qDebug() << "DialogBrick: Selected file:" << selectedFile << ", updated lastDir:" << lastDir;
    } else {
        qDebug() << "DialogBrick: Open cancelled";
    }
    return selectedFile;
}

QString DialogBrick::getSaveFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter) {
    qDebug() << "DialogBrick: getSaveFileName called, parent:" << parent << ", caption:" << caption << ", dir:" << dir << ", filter:" << filter;
    QString selectedFile = QFileDialog::getSaveFileName(parent, caption, dir.isEmpty() ? lastDir : dir, filter);
    if (!selectedFile.isEmpty()) {
        lastDir = QFileInfo(selectedFile).absolutePath();
        qDebug() << "DialogBrick: Selected save file:" << selectedFile << ", updated lastDir:" << lastDir;
    } else {
        qDebug() << "DialogBrick: Save cancelled";
    }
    return selectedFile;
}
