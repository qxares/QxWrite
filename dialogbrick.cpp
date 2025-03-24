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
    driveModel = new QFileSystemModel(this);
    driveModel->setRootPath("/");
    driveModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);  // Exclude '.' and '..' in drive view (right pane)

    dirModel = new QFileSystemModel(this);
    dirModel->setRootPath(lastDir);
    dirModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);  // Exclude '.' and '..' in directory view (middle pane)

    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath(lastDir);
    fileModel->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDot);  // Include '..' but exclude '.' in file view (left pane)

    fileView = new QListView();  // Left pane: File list
    dirView = new QTreeView();   // Middle pane: Directory tree
    driveView = new QTreeView(); // Right pane: Drive list
    fileTypeCombo = new QComboBox();
    fileNameEdit = new QLineEdit();

    qDebug() << "DialogBrick initialized with lastDir:" << lastDir;
}

QString DialogBrick::getSaveFileName(const QString &caption, const QString &dir, const QString &filter) {
    QDialog dialog;
    dialog.setWindowTitle(caption.isEmpty() ? "Save File" : caption);
    dialog.setModal(true);
    dialog.setFixedSize(700, 500);

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
    QString startDir = dir.isEmpty() ? lastDir : dir;
    dirModel->setRootPath(startDir);
    dirView->setModel(dirModel);
    dirView->setRootIndex(dirModel->index(startDir));
    dirView->hideColumn(1);
    dirView->hideColumn(2);
    dirView->hideColumn(3);

    // File Pane (Left)
    fileModel->setRootPath(startDir);
    QStringList filters = filter.mid(filter.indexOf("(") + 1, filter.indexOf(")") - filter.indexOf("(") - 1).split(" ");
    fileModel->setNameFilters(filters);
    fileModel->setNameFilterDisables(true);  // Ensure non-matching entries (like directories) are visible but disabled
    fileView->setModel(fileModel);
    fileView->setRootIndex(fileModel->index(startDir));

    // Debug: Log what QFileSystemModel is showing in the file view (left pane)
    QStringList fileEntries;
    for (int i = 0; i < fileModel->rowCount(fileView->rootIndex()); ++i) {
        QModelIndex index = fileModel->index(i, 0, fileView->rootIndex());
        fileEntries << fileModel->fileName(index);
    }
    qDebug() << "DialogBrick: File view (left pane) contents in" << startDir << ":" << fileEntries;

    // Filename Input
    QLabel *fileNameLabel = new QLabel("File name:", &dialog);
    fileNameEdit->setPlaceholderText("Enter filename");

    // Extension Dropdown
    QLabel *fileTypeLabel = new QLabel("Save as type:", &dialog);
    QStringList extensions = filters;
    for (QString &ext : extensions) {
        ext = ext.mid(1); // Remove leading '*'
    }
    fileTypeCombo->addItems(extensions);
    fileTypeCombo->setCurrentIndex(0);

    // Buttons
    QPushButton *saveButton = new QPushButton("Save", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);

    // Layout Setup (File view on left, dir view in middle, drive view on right)
    paneLayout->addWidget(fileView);  // Left: File list
    paneLayout->addWidget(dirView);   // Middle: Directory tree
    paneLayout->addWidget(driveView); // Right: Drive list

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
        lastDir = path;
        qDebug() << "DialogBrick: Drive view (right pane) clicked, navigated to:" << path;

        // Debug: Log file view contents after navigation
        QStringList fileEntries;
        for (int i = 0; i < fileModel->rowCount(fileView->rootIndex()); ++i) {
            QModelIndex idx = fileModel->index(i, 0, fileView->rootIndex());
            fileEntries << fileModel->fileName(idx);
        }
        qDebug() << "DialogBrick: File view (left pane) contents after drive navigation:" << fileEntries;
    });

    connect(dirView, &QTreeView::clicked, [&](const QModelIndex &index) {
        QString path = dirModel->filePath(index);
        fileModel->setRootPath(path);
        fileView->setRootIndex(fileModel->index(path));
        lastDir = path;
        qDebug() << "DialogBrick: Directory view (middle pane) clicked, navigated to:" << path;

        // Debug: Log file view contents after navigation
        QStringList fileEntries;
        for (int i = 0; i < fileModel->rowCount(fileView->rootIndex()); ++i) {
            QModelIndex idx = fileModel->index(i, 0, fileView->rootIndex());
            fileEntries << fileModel->fileName(idx);
        }
        qDebug() << "DialogBrick: File view (left pane) contents after dir navigation:" << fileEntries;
    });

    connect(fileView, &QListView::clicked, [&](const QModelIndex &index) {
        if (index.isValid()) {
            QString fileName = fileModel->fileName(index);
            QFileInfo fileInfo(fileModel->filePath(index));
            if (fileInfo.isFile()) {
                fileNameEdit->setText(fileName.section('.', 0, -2)); // Strip extension
                QString ext = "." + fileName.section('.', -1);
                int extIndex = fileTypeCombo->findText(ext);
                if (extIndex != -1) fileTypeCombo->setCurrentIndex(extIndex);
                qDebug() << "DialogBrick: File clicked in file view (left pane):" << fileName;
            }
        }
    });

    connect(fileView, &QListView::doubleClicked, [&](const QModelIndex &index) {
        if (index.isValid()) {
            QString path = fileModel->filePath(index);
            QFileInfo fileInfo(path);
            if (fileInfo.isDir()) {
                if (fileInfo.fileName() == "..") {
                    // Navigate to parent directory
                    QDir dir(fileModel->filePath(fileView->rootIndex()));
                    if (dir.cdUp()) {  // Check if we can go up (won't work at root)
                        QString parentPath = dir.absolutePath();
                        fileModel->setRootPath(parentPath);
                        fileView->setRootIndex(fileModel->index(parentPath));
                        dirModel->setRootPath(parentPath);
                        dirView->setRootIndex(dirModel->index(parentPath));
                        lastDir = parentPath;
                        qDebug() << "DialogBrick: Navigated to parent directory:" << parentPath;
                    } else {
                        qDebug() << "DialogBrick: Already at root directory, cannot navigate up";
                    }
                } else {
                    // Navigate into subdirectory
                    fileModel->setRootPath(path);
                    fileView->setRootIndex(fileModel->index(path));
                    dirModel->setRootPath(path);
                    dirView->setRootIndex(dirModel->index(path));
                    lastDir = path;
                    qDebug() << "DialogBrick: Navigated to subdirectory:" << path;
                }
                fileNameEdit->clear();

                // Debug: Log file view contents after navigation
                QStringList fileEntries;
                for (int i = 0; i < fileModel->rowCount(fileView->rootIndex()); ++i) {
                    QModelIndex idx = fileModel->index(i, 0, fileView->rootIndex());
                    fileEntries << fileModel->fileName(idx);
                }
                qDebug() << "DialogBrick: File view (left pane) contents after navigation:" << fileEntries;
            } else {
                lastDir = fileModel->rootPath();
                dialog.accept();
                qDebug() << "DialogBrick: File double-clicked, accepting:" << path;
            }
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
    qDebug() << "DialogBrick: Save cancelled";
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

    // Drives Pane (Right)
    driveView->setModel(driveModel);
    driveView->setMinimumWidth(200);
    driveView->setRootIndex(driveModel->index("/"));
    driveView->hideColumn(1);
    driveView->hideColumn(2);
    driveView->hideColumn(3);

    // Directory Pane (Middle)
    QString startDir = dir.isEmpty() ? lastDir : dir;
    dirModel->setRootPath(startDir);
    dirView->setModel(dirModel);
    dirView->setRootIndex(dirModel->index(startDir));
    dirView->hideColumn(1);
    dirView->hideColumn(2);
    dirView->hideColumn(3);

    // File Pane (Left)
    fileModel->setRootPath(startDir);
    QStringList filters = filter.mid(filter.indexOf("(") + 1, filter.indexOf(")") - filter.indexOf("(") - 1).split(" ");
    fileModel->setNameFilters(filters);
    fileModel->setNameFilterDisables(true);  // Ensure non-matching entries (like directories) are visible but disabled
    fileView->setModel(fileModel);
    fileView->setRootIndex(fileModel->index(startDir));

    // Debug: Log what QFileSystemModel is showing in the file view (left pane)
    QStringList fileEntries;
    for (int i = 0; i < fileModel->rowCount(fileView->rootIndex()); ++i) {
        QModelIndex index = fileModel->index(i, 0, fileView->rootIndex());
        fileEntries << fileModel->fileName(index);
    }
    qDebug() << "DialogBrick: File view (left pane) contents in" << startDir << ":" << fileEntries;

    // Filename Input (read-only for open dialog)
    QLabel *fileNameLabel = new QLabel("File name:", &dialog);
    fileNameEdit->setReadOnly(true);

    // Extension Dropdown
    QLabel *fileTypeLabel = new QLabel("Files of type:", &dialog);
    QStringList extensions = filters;
    for (QString &ext : extensions) {
        ext = ext.mid(1); // Remove '*'
    }
    fileTypeCombo->addItems(extensions);
    fileTypeCombo->setCurrentIndex(0);

    // Buttons
    QPushButton *openButton = new QPushButton("Open", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);

    // Layout Setup (File view on left, dir view in middle, drive view on right)
    paneLayout->addWidget(fileView);  // Left: File list
    paneLayout->addWidget(dirView);   // Middle: Directory tree
    paneLayout->addWidget(driveView); // Right: Drive list

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
        lastDir = path;
        qDebug() << "DialogBrick: Drive view (right pane) clicked, navigated to:" << path;

        // Debug: Log file view contents after navigation
        QStringList fileEntries;
        for (int i = 0; i < fileModel->rowCount(fileView->rootIndex()); ++i) {
            QModelIndex idx = fileModel->index(i, 0, fileView->rootIndex());
            fileEntries << fileModel->fileName(idx);
        }
        qDebug() << "DialogBrick: File view (left pane) contents after drive navigation:" << fileEntries;
    });

    connect(dirView, &QTreeView::clicked, [&](const QModelIndex &index) {
        QString path = dirModel->filePath(index);
        fileModel->setRootPath(path);
        fileView->setRootIndex(fileModel->index(path));
        lastDir = path;
        qDebug() << "DialogBrick: Directory view (middle pane) clicked, navigated to:" << path;

        // Debug: Log file view contents after navigation
        QStringList fileEntries;
        for (int i = 0; i < fileModel->rowCount(fileView->rootIndex()); ++i) {
            QModelIndex idx = fileModel->index(i, 0, fileView->rootIndex());
            fileEntries << fileModel->fileName(idx);
        }
        qDebug() << "DialogBrick: File view (left pane) contents after dir navigation:" << fileEntries;
    });

    connect(fileView, &QListView::clicked, [&](const QModelIndex &index) {
        if (index.isValid()) {
            QString fileName = fileModel->fileName(index);
            QFileInfo fileInfo(fileModel->filePath(index));
            if (fileInfo.isFile()) {
                fileNameEdit->setText(fileName);
                qDebug() << "DialogBrick: File clicked in file view (left pane):" << fileName;
            }
        }
    });

    connect(fileView, &QListView::doubleClicked, [&](const QModelIndex &index) {
        if (index.isValid()) {
            QString path = fileModel->filePath(index);
            QFileInfo fileInfo(path);
            if (fileInfo.isDir()) {
                if (fileInfo.fileName() == "..") {
                    // Navigate to parent directory
                    QDir dir(fileModel->filePath(fileView->rootIndex()));
                    if (dir.cdUp()) {  // Check if we can go up (won't work at root)
                        QString parentPath = dir.absolutePath();
                        fileModel->setRootPath(parentPath);
                        fileView->setRootIndex(fileModel->index(parentPath));
                        dirModel->setRootPath(parentPath);
                        dirView->setRootIndex(dirModel->index(parentPath));
                        lastDir = parentPath;
                        qDebug() << "DialogBrick: Navigated to parent directory:" << parentPath;
                    } else {
                        qDebug() << "DialogBrick: Already at root directory, cannot navigate up";
                    }
                } else {
                    // Navigate into subdirectory
                    fileModel->setRootPath(path);
                    fileView->setRootIndex(fileModel->index(path));
                    dirModel->setRootPath(path);
                    dirView->setRootIndex(dirModel->index(path));
                    lastDir = path;
                    qDebug() << "DialogBrick: Navigated to subdirectory:" << path;
                }
                fileNameEdit->clear();

                // Debug: Log file view contents after navigation
                QStringList fileEntries;
                for (int i = 0; i < fileModel->rowCount(fileView->rootIndex()); ++i) {
                    QModelIndex idx = fileModel->index(i, 0, fileView->rootIndex());
                    fileEntries << fileModel->fileName(idx);
                }
                qDebug() << "DialogBrick: File view (left pane) contents after navigation:" << fileEntries;
            } else {
                lastDir = fileModel->rootPath();
                dialog.accept();
                qDebug() << "DialogBrick: File double-clicked, accepting:" << path;
            }
        }
    });

    connect(fileTypeCombo, &QComboBox::currentTextChanged, [&](const QString &text) {
        fileModel->setNameFilters({QString("*%1").arg(text)});
        qDebug() << "DialogBrick: File type filter changed to:" << text;

        // Debug: Log file view contents after filter change
        QStringList fileEntries;
        for (int i = 0; i < fileModel->rowCount(fileView->rootIndex()); ++i) {
            QModelIndex idx = fileModel->index(i, 0, fileView->rootIndex());
            fileEntries << fileModel->fileName(idx);
        }
        qDebug() << "DialogBrick: File view (left pane) contents after filter change:" << fileEntries;
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
    qDebug() << "DialogBrick: Open cancelled";
    return QString();
}
