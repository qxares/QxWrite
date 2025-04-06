#ifndef DIALOGBRICK_H
#define DIALOGBRICK_H

#include <QObject>
#include <QFileDialog>

class DialogBrick : public QObject {
    Q_OBJECT
public:
    explicit DialogBrick(QObject *parent = nullptr);
    QString getOpenFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter);
    QString getSaveFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter);
    QString getSelectedFilter() const;

private:
    QString lastDir;
    QString selectedFilter;
};

#endif // DIALOGBRICK_H
