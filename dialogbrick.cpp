#include "dialogbrick.h"
#include <QFileDialog>
#include <QDebug>

DialogBrick::DialogBrick(QObject *parent) : QObject(parent), lastDir(QDir::homePath()) {
    qDebug() << "DialogBrick initialized with lastDir:" << lastDir;
}

QString DialogBrick::getOpenFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter) {
    QFileDialog dialog(parent, caption, !dir.isEmpty() ? dir : lastDir, filter);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true); // Force Qt dialog

    qDebug() << "DialogBrick: getOpenFileName called with parent:" << parent
             << "caption:" << caption << "dir:" << dialog.directory().path()
             << "filter:" << filter;

    QStringList files;
    if (dialog.exec() == QDialog::Accepted) {
        files = dialog.selectedFiles();
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
             << QDir(dialog.directory().path()).entryList(QDir::Files | QDir::Dirs | QDir::NoDot);
    return QString();
}

QString DialogBrick::getSaveFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter) {
    QFileDialog dialog(parent, caption, !dir.isEmpty() ? dir : lastDir, filter);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);

    qDebug() << "DialogBrick: getSaveFileName called with parent:" << parent
             << "caption:" << caption << "dir:" << dialog.directory().path()
             << "filter:" << filter;

    QStringList files;
    if (dialog.exec() == QDialog::Accepted) {
        files = dialog.selectedFiles();
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
