#include "dialogbrick.h"
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeView>
#include <QListView>
#include <QPushButton>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QDebug>

DialogBrick::DialogBrick(QObject *parent) : QObject(parent), lastDir("/home/ares") {
    qDebug() << "DialogBrick initialized with lastDir:" << lastDir;
}

QString DialogBrick::getSaveFileName(const QString &caption, const QString &dir, const QString &filter) {
    QDialog dialog;
    dialog.setWindowTitle(caption.isEmpty() ? "Save File" : caption);
    dialog.setModal(true);
    dialog.setFixedSize(700, 500); // Slightly larger for better layout

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    QHBoxLayout *paneLayout = new QHBoxLayout;
    QHBoxLayout *inputLayout = new QHBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // Drives Pane
    QTreeView *driveView = new QTreeView(&dialog);
    QFileSystemModel *driveModel = new QFileSystemModel(&dialog);
    driveModel->setRootPath("/");
    driveModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    driveView->setModel(driveModel);
    driveView->setMinimumWidth(200);
    driveView->setRootIndex(driveModel->index("/home/ares"));
    driveView->hideColumn(1);
    driveView->hideColumn(2);
    driveView->hideColumn(3);

    // Directory Pane
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

    // File Pane
    QListView *fileView = new QListView(&dialog);
    QFileSystemModel *fileModel = new QFileSystemModel(&dialog);
    fileModel->setRootPath(startDir);
    QStringList filters = filter.mid(filter.indexOf("(") + 1, filter.indexOf(")") - filter.indexOf("(") - 1).split(" ");
    fileModel->setNameFilters(filters);
    fileModel->setNameFilterDisables(false);
    fileModel->setFilter(QDir::Files);
    fileView->setModel(fileModel);
    fileView->setRootIndex(fileModel->index(startDir));

    // Filename Input
    QLabel *fileNameLabel = new QLabel("File name:", &dialog);
    QLineEdit *fileNameEdit = new QLineEdit(&dialog);
    fileNameEdit->setPlaceholderText("Enter filename");

    // Extension Dropdown
    QLabel *fileTypeLabel = new QLabel("Save as type:", &dialog);
    QComboBox *fileTypeCombo = new QComboBox(&dialog);
    QStringList extensions = filters;
    for (QString &ext : extensions) {
        ext = ext.mid(1); // Remove leading '*'
    }
    fileTypeCombo->addItems(extensions);
    fileTypeCombo->setCurrentIndex(0); // Default to first extension

    // Buttons
    QPushButton *saveButton = new QPushButton("Save", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);

    // Layout Setup
    paneLayout->addWidget(driveView);
    paneLayout->addWidget(dirView);
    paneLayout->addWidget(fileView);

    inputLayout->addWidget(fileNameLabel);
    inputLayout->addWidget(fileNameEdit);
    inputLayout->addWidget(fileTypeLabel);
    inputLayout->addWidget(fileTypeCombo);

    buttonLayout->addStretch();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(paneLayout);
    mainLayout->addLayout(inputLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(buttonLayout);

    // Connections
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

    connect(fileView, &QListView::clicked, [&](const QModelIndex &index) {
        if (index.isValid()) {
            QString fileName = fileModel->fileName(index);
            fileNameEdit->setText(fileName.section('.', 0, -2)); // Strip extension
            QString ext = "." + fileName.section('.', -1);
            int extIndex = fileTypeCombo->findText(ext);
            if (extIndex != -1) fileTypeCombo->setCurrentIndex(extIndex);
        }
    });

    connect(saveButton, &QPushButton::clicked, [&]() {
        QString fileName = fileNameEdit->text().trimmed();
        if (!fileName.isEmpty()) {
            lastDir = fileModel->rootPath();
            dialog.accept();
        }
    });

    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QString fileName = fileNameEdit->text().trimmed();
        if (!fileName.isEmpty()) {
            QString ext = fileTypeCombo->currentText();
            if (!fileName.endsWith(ext)) fileName += ext;
            QString filePath = QDir(lastDir).filePath(fileName);
            qDebug() << "DialogBrick: Save selected:" << filePath;
            return filePath;
        }
    }
    qDebug() << "DialogBrick: Save selected: \"\"";
    return QString();
}

QString DialogBrick::getOpenFileName(const QString &caption, const QString &dir, const QString &filter) {
    QDialog dialog;
    dialog.setWindowTitle(caption.isEmpty() ? "Open File" : caption);
    dialog.setModal(true);
    dialog.setFixedSize(700, 500);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    QHBoxLayout *paneLayout = new QHBoxLayout;
    QHBoxLayout *inputLayout = new QHBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // Drives Pane
    QTreeView *driveView = new QTreeView(&dialog);
    QFileSystemModel *driveModel = new QFileSystemModel(&dialog);
    driveModel->setRootPath("/");
    driveModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    driveView->setModel(driveModel);
    driveView->setMinimumWidth(200);
    driveView->setRootIndex(driveModel->index("/home/ares"));
    driveView->hideColumn(1);
    driveView->hideColumn(2);
    driveView->hideColumn(3);

    // Directory Pane
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

    // File Pane
    QListView *fileView = new QListView(&dialog);
    QFileSystemModel *fileModel = new QFileSystemModel(&dialog);
    fileModel->setRootPath(startDir);
    QStringList filters = filter.mid(filter.indexOf("(") + 1, filter.indexOf(")") - filter.indexOf("(") - 1).split(" ");
    fileModel->setNameFilters(filters);
    fileModel->setNameFilterDisables(false);
    fileModel->setFilter(QDir::Files);
    fileView->setModel(fileModel);
    fileView->setRootIndex(fileModel->index(startDir));

    // Filename Input (for consistency, but read-only here)
    QLabel *fileNameLabel = new QLabel("File name:", &dialog);
    QLineEdit *fileNameEdit = new QLineEdit(&dialog);
    fileNameEdit->setReadOnly(true); // Open dialog just selects existing files

    // Extension Dropdown
    QLabel *fileTypeLabel = new QLabel("Files of type:", &dialog);
    QComboBox *fileTypeCombo = new QComboBox(&dialog);
    QStringList extensions = filters;
    for (QString &ext : extensions) {
        ext = ext.mid(1); // Remove '*'
    }
    fileTypeCombo->addItems(extensions);
    fileTypeCombo->setCurrentIndex(0);

    // Buttons
    QPushButton *openButton = new QPushButton("Open", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);

    // Layout Setup
    paneLayout->addWidget(driveView);
    paneLayout->addWidget(dirView);
    paneLayout->addWidget(fileView);

    inputLayout->addWidget(fileNameLabel);
    inputLayout->addWidget(fileNameEdit);
    inputLayout->addWidget(fileTypeLabel);
    inputLayout->addWidget(fileTypeCombo);

    buttonLayout->addStretch();
    buttonLayout->addWidget(openButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(paneLayout);
    mainLayout->addLayout(inputLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(buttonLayout);

    // Connections
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

    connect(fileView, &QListView::clicked, [&](const QModelIndex &index) {
        if (index.isValid()) {
            fileNameEdit->setText(fileModel->fileName(index));
        }
    });

    connect(fileView, &QListView::doubleClicked, [&]() {
        if (fileView->currentIndex().isValid()) {
            lastDir = fileModel->rootPath();
            dialog.accept();
        }
    });

    connect(fileTypeCombo, &QComboBox::currentTextChanged, [&](const QString &text) {
        fileModel->setNameFilters({QString("*%1").arg(text)});
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
