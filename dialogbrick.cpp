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
#include <QDir>
#include <QDebug>

DialogBrick::DialogBrick(QObject *parent) : QObject(parent), lastDir("/home/ares") {
    qDebug() << "DialogBrick initialized with lastDir:" << lastDir;
}

QString DialogBrick::getSaveFileName(const QString &caption, const QString &dir, const QString &filter) {
    QDialog dialog;
    dialog.setWindowTitle(caption.isEmpty() ? "Save File" : caption);
    dialog.setModal(true);
    dialog.setFixedSize(700, 500);

    QFileSystemModel *driveModel = new QFileSystemModel(&dialog);
    driveModel->setRootPath("/");
    driveModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    QFileSystemModel *dirModel = new QFileSystemModel(&dialog);
    QString startDir = dir.isEmpty() ? lastDir : dir;
    dirModel->setRootPath(startDir);
    dirModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    QFileSystemModel *fileModel = new QFileSystemModel(&dialog);
    fileModel->setRootPath(startDir);
    fileModel->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDot);

    QTreeView *driveView = new QTreeView(&dialog);
    QTreeView *dirView = new QTreeView(&dialog);
    QListView *fileView = new QListView(&dialog);
    QComboBox *fileTypeCombo = new QComboBox(&dialog);
    QLineEdit *fileNameEdit = new QLineEdit(&dialog);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    QHBoxLayout *paneLayout = new QHBoxLayout;
    QHBoxLayout *inputLayout = new QHBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // Drives Pane (Right)
    driveView->setModel(driveModel);
    driveView->setMinimumWidth(200);
    driveView->setRootIndex(driveModel->index("/"));
    driveView->hideColumn(1);
    driveView->hideColumn(2);
    driveView->hideColumn(3);

    // Directory Pane (Middle)
    dirView->setModel(dirModel);
    dirView->setRootIndex(dirModel->index(startDir));
    dirView->hideColumn(1);
    dirView->hideColumn(2);
    dirView->hideColumn(3);

    // File Pane (Left)
    QStringList filters = filter.mid(filter.indexOf("(") + 1, filter.indexOf(")") - filter.indexOf("(") - 1).split(" ");
    fileModel->setNameFilters(filters);
    fileModel->setNameFilterDisables(true);
    fileView->setModel(fileModel);
    fileView->setRootIndex(fileModel->index(startDir));

    // Debug: Log file view contents
    QStringList fileEntries;
    for (int i = 0; i < fileModel->rowCount(fileView->rootIndex()); ++i) {
        fileEntries << fileModel->fileName(fileModel->index(i, 0, fileView->rootIndex()));
    }
    qDebug() << "DialogBrick: File view (left pane) contents in" << startDir << ":" << fileEntries;

    // UI Elements
    QLabel *fileNameLabel = new QLabel("File name:", &dialog);
    fileNameEdit->setPlaceholderText("Enter filename");
    QLabel *fileTypeLabel = new QLabel("Save as type:", &dialog);
    QStringList extensions = filters;
    for (QString &ext : extensions) ext = ext.mid(1);
    fileTypeCombo->addItems(extensions);
    fileTypeCombo->setCurrentIndex(0);

    QPushButton *saveButton = new QPushButton("Save", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);

    // Layout
    paneLayout->addWidget(fileView);  // Left: Files
    paneLayout->addWidget(dirView);   // Middle: Dirs
    paneLayout->addWidget(driveView); // Right: Drives
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
    QString selectedFile;
    connect(driveView, &QTreeView::clicked, [&](const QModelIndex &index) {
        QString path = driveModel->filePath(index);
        dirModel->setRootPath(path);
        dirView->setRootIndex(dirModel->index(path));
        fileModel->setRootPath(path);
        fileView->setRootIndex(fileModel->index(path));
        lastDir = path;
        qDebug() << "DialogBrick: Drive view (right pane) clicked, navigated to:" << path;
    });

    connect(dirView, &QTreeView::clicked, [&](const QModelIndex &index) {
        QString path = dirModel->filePath(index);
        fileModel->setRootPath(path);
        fileView->setRootIndex(fileModel->index(path));
        lastDir = path;
        qDebug() << "DialogBrick: Directory view (middle pane) clicked, navigated to:" << path;
    });

    connect(fileView, &QListView::doubleClicked, [&](const QModelIndex &index) {
        QString path = fileModel->filePath(index);
        QFileInfo fileInfo(path);
        if (fileInfo.isDir()) {
            fileModel->setRootPath(path);
            fileView->setRootIndex(fileModel->index(path));
            dirModel->setRootPath(path);
            dirView->setRootIndex(dirModel->index(path));
            lastDir = path;
            qDebug() << "DialogBrick: Navigated to subdirectory:" << path;
        } else {
            selectedFile = path;
            dialog.accept();
            qDebug() << "DialogBrick: File double-clicked, accepting:" << path;
        }
    });

    connect(saveButton, &QPushButton::clicked, [&]() {
        QString fileName = fileNameEdit->text().trimmed();
        if (!fileName.isEmpty()) {
            QString ext = fileTypeCombo->currentText();
            if (!fileName.endsWith(ext)) fileName += ext;
            selectedFile = QDir(lastDir).filePath(fileName);
            dialog.accept();
        }
    });

    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted && !selectedFile.isEmpty()) {
        lastDir = QFileInfo(selectedFile).absolutePath();
        qDebug() << "DialogBrick: Save selected:" << selectedFile;
        return selectedFile;
    }
    qDebug() << "DialogBrick: Save cancelled";
    return QString();
}

QString DialogBrick::getOpenFileName(const QString &caption, const QString &dir, const QString &filter) {
    QDialog dialog;
    dialog.setWindowTitle(caption.isEmpty() ? "Open File" : caption);
    dialog.setModal(true);
    dialog.setFixedSize(700, 500);

    QFileSystemModel *driveModel = new QFileSystemModel(&dialog);
    driveModel->setRootPath("/");
    driveModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    QFileSystemModel *dirModel = new QFileSystemModel(&dialog);
    QString startDir = dir.isEmpty() ? lastDir : dir;
    dirModel->setRootPath(startDir);
    dirModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    QFileSystemModel *fileModel = new QFileSystemModel(&dialog);
    fileModel->setRootPath(startDir);
    fileModel->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDot);

    QTreeView *driveView = new QTreeView(&dialog);
    QTreeView *dirView = new QTreeView(&dialog);
    QListView *fileView = new QListView(&dialog);
    QComboBox *fileTypeCombo = new QComboBox(&dialog);
    QLineEdit *fileNameEdit = new QLineEdit(&dialog);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    QHBoxLayout *paneLayout = new QHBoxLayout;
    QHBoxLayout *inputLayout = new QHBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // Drives Pane (Right)
    driveView->setModel(driveModel);
    driveView->setMinimumWidth(200);
    driveView->setRootIndex(driveModel->index("/"));
    driveView->hideColumn(1);
    driveView->hideColumn(2);
    driveView->hideColumn(3);

    // Directory Pane (Middle)
    dirView->setModel(dirModel);
    dirView->setRootIndex(dirModel->index(startDir));
    dirView->hideColumn(1);
    dirView->hideColumn(2);
    dirView->hideColumn(3);

    // File Pane (Left)
    QStringList filters = filter.mid(filter.indexOf("(") + 1, filter.indexOf(")") - filter.indexOf("(") - 1).split(" ");
    fileModel->setNameFilters(filters);
    fileModel->setNameFilterDisables(true);
    fileView->setModel(fileModel);
    fileView->setRootIndex(fileModel->index(startDir));

    // Debug: Log file view contents
    QStringList fileEntries;
    for (int i = 0; i < fileModel->rowCount(fileView->rootIndex()); ++i) {
        fileEntries << fileModel->fileName(fileModel->index(i, 0, fileView->rootIndex()));
    }
    qDebug() << "DialogBrick: File view (left pane) contents in" << startDir << ":" << fileEntries;

    // UI Elements
    QLabel *fileNameLabel = new QLabel("File name:", &dialog);
    fileNameEdit->setReadOnly(true);
    QLabel *fileTypeLabel = new QLabel("Files of type:", &dialog);
    QStringList extensions = filters;
    for (QString &ext : extensions) ext = ext.mid(1);
    fileTypeCombo->addItems(extensions);
    fileTypeCombo->setCurrentIndex(0);

    QPushButton *openButton = new QPushButton("Open", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);

    // Layout
    paneLayout->addWidget(fileView);  // Left: Files
    paneLayout->addWidget(dirView);   // Middle: Dirs
    paneLayout->addWidget(driveView); // Right: Drives
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
    QString selectedFile;
    connect(driveView, &QTreeView::clicked, [&](const QModelIndex &index) {
        QString path = driveModel->filePath(index);
        dirModel->setRootPath(path);
        dirView->setRootIndex(dirModel->index(path));
        fileModel->setRootPath(path);
        fileView->setRootIndex(fileModel->index(path));
        lastDir = path;
        qDebug() << "DialogBrick: Drive view (right pane) clicked, navigated to:" << path;
    });

    connect(dirView, &QTreeView::clicked, [&](const QModelIndex &index) {
        QString path = dirModel->filePath(index);
        fileModel->setRootPath(path);
        fileView->setRootIndex(fileModel->index(path));
        lastDir = path;
        qDebug() << "DialogBrick: Directory view (middle pane) clicked, navigated to:" << path;
    });

    connect(fileView, &QListView::clicked, [&](const QModelIndex &index) {
        if (index.isValid()) {
            QFileInfo fileInfo(fileModel->filePath(index));
            if (fileInfo.isFile()) {
                fileNameEdit->setText(fileModel->fileName(index));
                qDebug() << "DialogBrick: File clicked in file view (left pane):" << fileModel->fileName(index);
            }
        }
    });

    connect(fileView, &QListView::doubleClicked, [&](const QModelIndex &index) {
        QString path = fileModel->filePath(index);
        QFileInfo fileInfo(path);
        if (fileInfo.isDir()) {
            fileModel->setRootPath(path);
            fileView->setRootIndex(fileModel->index(path));
            dirModel->setRootPath(path);
            dirView->setRootIndex(dirModel->index(path));
            lastDir = path;
            fileNameEdit->clear();
            qDebug() << "DialogBrick: Navigated to subdirectory:" << path;
        } else {
            selectedFile = path;
            dialog.accept();
            qDebug() << "DialogBrick: File double-clicked, accepting:" << path;
        }
    });

    connect(fileTypeCombo, &QComboBox::currentTextChanged, [&](const QString &text) {
        fileModel->setNameFilters({QString("*%1").arg(text)});
        qDebug() << "DialogBrick: File type filter changed to:" << text;
    });

    connect(openButton, &QPushButton::clicked, [&]() {
        if (fileView->currentIndex().isValid()) {
            selectedFile = fileModel->filePath(fileView->currentIndex());
            dialog.accept();
        }
    });

    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted && !selectedFile.isEmpty()) {
        lastDir = QFileInfo(selectedFile).absolutePath();
        qDebug() << "DialogBrick: Open selected:" << selectedFile;
        return selectedFile;
    }
    qDebug() << "DialogBrick: Open cancelled";
    return QString();
}
