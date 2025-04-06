#include "dialogbrick.h"
#include <QDebug>
#include <QFileDialog>

DialogBrick::DialogBrick(QObject *parent) : QObject(parent), lastDir("/home/ares") {
    qDebug() << "DialogBrick initialized with lastDir:" << lastDir;
}

QString DialogBrick::getOpenFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter) {
    QFileDialog dialog(parent, caption, dir.isEmpty() ? lastDir : dir, filter);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true); // Force Qt dialog, not Nemo
    dialog.setWindowTitle("QxWrite Open File"); // Custom title for vibe
    qDebug() << "DialogBrick: getOpenFileName called with parent:" << parent 
             << "caption:" << caption << "dir:" << dir << "filter:" << filter;
    qDebug() << "DialogBrick: Dialog visible:" << dialog.isVisible();

    if (dialog.exec() == QDialog::Accepted) {
        QString fileName = dialog.selectedFiles().first();
        selectedFilter = dialog.selectedNameFilter();
        lastDir = QFileInfo(fileName).absolutePath();
        qDebug() << "DialogBrick: Selected filter:" << selectedFilter;
        qDebug() << "DialogBrick: Updated lastDir to:" << lastDir;
        qDebug() << "DialogBrick: QFileDialog returned:" << fileName;
        return fileName;
    }
    return "";
}

QString DialogBrick::getSaveFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter) {
    QFileDialog dialog(parent, caption, dir.isEmpty() ? lastDir : dir, filter);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true); // Force Qt dialog, not Nemo
    dialog.setWindowTitle("QxWrite Save File"); // Custom title for vibe
    qDebug() << "DialogBrick: getSaveFileName called with parent:" << parent 
             << "caption:" << caption << "dir:" << dir << "filter:" << filter;
    qDebug() << "DialogBrick: Dialog visible:" << dialog.isVisible();

    if (dialog.exec() == QDialog::Accepted) {
        QString fileName = dialog.selectedFiles().first();
        selectedFilter = dialog.selectedNameFilter();
        lastDir = QFileInfo(fileName).absolutePath();
        qDebug() << "DialogBrick: Selected filter:" << selectedFilter;
        qDebug() << "DialogBrick: Updated lastDir to:" << lastDir;
        qDebug() << "DialogBrick: QFileDialog returned:" << fileName;
        return fileName;
    }
    return "";
}

QString DialogBrick::getSelectedFilter() const {
    return selectedFilter;
}
