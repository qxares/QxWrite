#include "dialogbrick.h"
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeView>
#include <QListView>
#include <QPushButton>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QDebug>

DialogBrick::DialogBrick(QObject *parent) : QObject(parent), lastDir("/home/ares/Pictures/Aries") {
    qDebug() << "DialogBrick initialized with lastDir:" << lastDir;
}

QString DialogBrick::getSaveFileName(const QString &caption, const QString &dir, const QString &filter) {
    QDialog dialog;
    dialog.setWindowTitle(caption);
    dialog.setModal(true);
    dialog.setFixedSize(600, 400); // Wider for three panes

    QHBoxLayout *mainLayout = new QHBoxLayout(&dialog);
    QVBoxLayout *buttonLayout = new QVBoxLayout;

// ... [rest unchanged] ...
    // Drives (simplified as root dirs)
    QTreeView *driveView = new QTreeView(&dialog);
    QFileSystemModel *driveModel = new QFileSystemModel(&dialog);
    driveModel->setRootPath("/");
    driveModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    driveView->setModel(driveModel);
    driveView->setMaximumWidth(150); // Widened from 100
    driveView->setRootIndex(driveModel->index("/"));
    driveView->hideColumn(1);
    driveView->hideColumn(2);
    driveView->hideColumn(3);
// ... [rest unchanged] ...
    // Directory Tree
    QTreeView *dirView = new QTreeView(&dialog);
    QFileSystemModel *dirModel = new QFileSystemModel(&dialog);
    QString startDir = dir.isEmpty() ? lastDir : dir;
    dirModel->setRootPath(startDir);
    dirModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    dirView->setModel(dirModel);
    dirView->setRootIndex(dirModel->index(startDir));
    dirView->hideColumn(1);
    dirView->hideColumn(2);
    dirView->hideColumn(3);

    // File List
    QListView *fileView = new QListView(&dialog);
    QFileSystemModel *fileModel = new QFileSystemModel(&dialog);
    fileModel->setRootPath(startDir);
    QStringList filters = filter.mid(filter.indexOf("(") + 1, filter.indexOf(")") - filter.indexOf("(") - 1).split(" ");
    fileModel->setNameFilters(filters);
    fileModel->setNameFilterDisables(false);
    fileModel->setFilter(QDir::Files);
    fileView->setModel(fileModel);
    fileView->setRootIndex(fileModel->index(startDir));

    QPushButton *saveButton = new QPushButton("Save", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);

    mainLayout->addWidget(driveView);
    mainLayout->addWidget(dirView);
    mainLayout->addWidget(fileView);
    mainLayout->addLayout(buttonLayout);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();

    connect(driveView, &QTreeView::clicked, [&](const QModelIndex &index) {
        QString path = driveModel->filePath(index);
        dirModel->setRootPath(path);
        dirView->setRootIndex(dirModel->index(path));
        fileModel->setRootPath(path);
        fileView->setRootIndex(fileModel->index(path));
    });

    connect(dirView, &QTreeView::clicked, [&](const QModelIndex &index) {
        QString path = dirModel->filePath(index);
        fileModel->setRootPath(path);
        fileView->setRootIndex(fileModel->index(path));
        lastDir = path;
    });

    connect(fileView, &QListView::doubleClicked, [&]() {
        if (fileView->currentIndex().isValid()) {
            lastDir = fileModel->rootPath();
            dialog.accept();
        }
    });

    connect(saveButton, &QPushButton::clicked, [&]() {
        if (fileView->currentIndex().isValid()) {
            lastDir = fileModel->rootPath();
            dialog.accept();
        }
    });

    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted && fileView->currentIndex().isValid()) {
        QString filePath = fileModel->filePath(fileView->currentIndex());
        qDebug() << "DialogBrick: Save selected:" << filePath;
        return filePath;
    }
    return QString();
}

QString DialogBrick::getOpenFileName(const QString &caption, const QString &dir, const QString &filter) {
    QDialog dialog;
    dialog.setWindowTitle(caption);
    dialog.setModal(true);
    dialog.setFixedSize(600, 400); // Wider for three panes

    QHBoxLayout *mainLayout = new QHBoxLayout(&dialog);
    QVBoxLayout *buttonLayout = new QVBoxLayout;

    // Drives (simplified as root dirs)
    QTreeView *driveView = new QTreeView(&dialog);
    QFileSystemModel *driveModel = new QFileSystemModel(&dialog);
    driveModel->setRootPath("/");
    driveModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    driveView->setModel(driveModel);
    driveView->setMaximumWidth(100);
    driveView->setRootIndex(driveModel->index("/"));
    driveView->hideColumn(1);
    driveView->hideColumn(2);
    driveView->hideColumn(3);

    // Directory Tree
    QTreeView *dirView = new QTreeView(&dialog);
    QFileSystemModel *dirModel = new QFileSystemModel(&dialog);
    QString startDir = dir.isEmpty() ? lastDir : dir;
    dirModel->setRootPath(startDir);
    dirModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    dirView->setModel(dirModel);
    dirView->setRootIndex(dirModel->index(startDir));
    dirView->hideColumn(1);
    dirView->hideColumn(2);
    dirView->hideColumn(3);

    // File List
    QListView *fileView = new QListView(&dialog);
    QFileSystemModel *fileModel = new QFileSystemModel(&dialog);
    fileModel->setRootPath(startDir);
    QStringList filters = filter.mid(filter.indexOf("(") + 1, filter.indexOf(")") - filter.indexOf("(") - 1).split(" ");
    fileModel->setNameFilters(filters);
    fileModel->setNameFilterDisables(false);
    fileModel->setFilter(QDir::Files);
    fileView->setModel(fileModel);
    fileView->setRootIndex(fileModel->index(startDir));

    QPushButton *openButton = new QPushButton("Open", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);

    mainLayout->addWidget(driveView);
    mainLayout->addWidget(dirView);
    mainLayout->addWidget(fileView);
    mainLayout->addLayout(buttonLayout);
    buttonLayout->addWidget(openButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();

    connect(driveView, &QTreeView::clicked, [&](const QModelIndex &index) {
        QString path = driveModel->filePath(index);
        dirModel->setRootPath(path);
        dirView->setRootIndex(dirModel->index(path));
        fileModel->setRootPath(path);
        fileView->setRootIndex(fileModel->index(path));
    });

    connect(dirView, &QTreeView::clicked, [&](const QModelIndex &index) {
        QString path = dirModel->filePath(index);
        fileModel->setRootPath(path);
        fileView->setRootIndex(fileModel->index(path));
        lastDir = path;
    });

    connect(fileView, &QListView::doubleClicked, [&]() {
        if (fileView->currentIndex().isValid()) {
            lastDir = fileModel->rootPath();
            dialog.accept();
        }
    });

    connect(openButton, &QPushButton::clicked, [&]() {
        if (fileView->currentIndex().isValid()) {
            lastDir = fileModel->rootPath();
            dialog.accept();
        }
    });

    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted && fileView->currentIndex().isValid()) {
        QString filePath = fileModel->filePath(fileView->currentIndex());
        qDebug() << "DialogBrick: Open selected:" << filePath;
        return filePath;
    }
    qDebug() << "DialogBrick: Open selected: \"\"";
    return QString();
}
