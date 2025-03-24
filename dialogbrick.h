#ifndef DIALOGBRICK_H
#define DIALOGBRICK_H

#include <QObject>
#include <QString>

class QFileSystemModel;
class QTreeView;
class QListView;
class QComboBox;
class QLineEdit;

class DialogBrick : public QObject {
    Q_OBJECT
public:
    DialogBrick(QObject *parent = nullptr);
    QString getSaveFileName(const QString &caption, const QString &dir, const QString &filter);
    QString getOpenFileName(const QString &caption, const QString &dir, const QString &filter);

private:
    QString lastDir;  // Persists the last directory
    QFileSystemModel *driveModel;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
    QTreeView *driveView;  // Left pane: Drive list
    QTreeView *dirView;    // Middle pane: Directory tree
    QListView *fileView;   // Right pane: File list
    QComboBox *fileTypeCombo;
    QLineEdit *fileNameEdit;
};

#endif // DIALOGBRICK_H
