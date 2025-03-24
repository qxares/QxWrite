#ifndef DIALOGBRICK_H
#define DIALOGBRICK_H

#include <QObject>
#include <QString>

class DialogBrick : public QObject {
    Q_OBJECT
public:
    DialogBrick(QObject *parent = nullptr);
    QString getSaveFileName(const QString &caption, const QString &dir, const QString &filter);
    QString getOpenFileName(const QString &caption, const QString &dir, const QString &filter);

private:
    QString lastDir;  // Add this
};

#endif // DIALOGBRICK_H
