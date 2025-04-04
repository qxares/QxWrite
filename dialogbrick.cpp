// dialogbrick.cpp
#include "dialogbrick.h"
#include <QFileDialog>
#include <QDebug>

DialogBrick::DialogBrick(QObject *parent) : QObject(parent), lastDir(QDir::homePath()) {
    qDebug() << "DialogBrick initialized with lastDir:" << lastDir;
}

QString DialogBrick::getOpenFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter) {
    QFileDialog dialog(parent, caption, !dir.isEmpty() ? dir : lastDir);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);  // Custom Qt dialog
    QStringList filters = filter.split(";;", Qt::SkipEmptyParts);
    dialog.setNameFilters(filters);  // Split filter for proper display

    qDebug() << "DialogBrick: getOpenFileName called with parent:" << parent
             << "caption:" << caption << "dir:" << dialog.directory().path()
             << "filter:" << filter;
    qDebug() << "DialogBrick: Dialog visible:" << dialog.isVisible();

    QStringList files;
    if (dialog.exec() == QDialog::Accepted) {
        files = dialog.selectedFiles();
        qDebug() << "DialogBrick: Selected filter:" << dialog.selectedNameFilter();
        if (!files.isEmpty()) {
            lastDir = QFileInfo(files.first()).absolutePath();
            qDebug() << "DialogBrick: Updated lastDir to:" << lastDir;
            qDebug() << "DialogBrick: QFileDialog returned:" << files.first();
            return files.first();
        }
    }

    qDebug() << "DialogBrick: QFileDialog returned: \"\"";
    qDebug() << "DialogBrick: Open cancelled";
    qDebug() << "DialogBrick: File view contents in" << dialog.directory().path() << ":"
             << QDir(dialog.directory().path()).entryList(dialog.nameFilters(), QDir::Files | QDir::NoDotAndDotDot);
    qDebug() << "DialogBrick: Raw dir contents:" << QDir(dialog.directory().path()).entryList(QDir::Files | QDir::NoDotAndDotDot);
    return QString();
}

QString DialogBrick::getSaveFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter) {
    QFileDialog dialog(parent, caption, !dir.isEmpty() ? dir : lastDir);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);  // Custom Qt dialog
    QStringList filters = filter.split(";;", Qt::SkipEmptyParts);
    dialog.setNameFilters(filters);  // Split filter for proper display

    qDebug() << "DialogBrick: getSaveFileName called with parent:" << parent
             << "caption:" << caption << "dir:" << dialog.directory().path()
             << "filter:" << filter;
    qDebug() << "DialogBrick: Dialog visible:" << dialog.isVisible();

    QStringList files;
    if (dialog.exec() == QDialog::Accepted) {
        files = dialog.selectedFiles();
        qDebug() << "DialogBrick: Selected filter:" << dialog.selectedNameFilter();
        if (!files.isEmpty()) {
            lastDir = QFileInfo(files.first()).absolutePath();
            qDebug() << "DialogBrick: Updated lastDir to:" << lastDir;
            qDebug() << "DialogBrick: QFileDialog returned:" << files.first();
            return files.first();
        }
    }

    qDebug() << "DialogBrick: QFileDialog returned: \"\"";
    return QString();
}
