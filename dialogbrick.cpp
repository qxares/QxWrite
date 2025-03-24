#include "dialogbrick.h"
#include <QFileDialog>
#include <QDebug>

DialogBrick::DialogBrick(QObject *parent) : QObject(parent) {
    qDebug() << "DialogBrick initialized";
}

QString DialogBrick::getSaveFileName(const QString &caption, const QString &dir, const QString &filter) {
    QString fileName = QFileDialog::getSaveFileName(nullptr, caption, dir, filter);
    if (!fileName.isEmpty()) {
        qDebug() << "DialogBrick: Save selected:" << fileName;
    }
    return fileName;
}

QString DialogBrick::getOpenFileName(const QString &caption, const QString &dir, const QString &filter) {
    QString fileName = QFileDialog::getOpenFileName(nullptr, caption, dir, filter);
    if (!fileName.isEmpty()) {
        qDebug() << "DialogBrick: Open selected:" << fileName;
    } else {
        qDebug() << "DialogBrick: Open selected: \"\"";
    }
    return fileName;
}
