#ifndef DIALOGBRICK_H
#define DIALOGBRICK_H

#include <QObject>
#include <QString>

class DialogBrick : public QObject {
    Q_OBJECT
public:
    explicit DialogBrick(QObject *parent = nullptr);
    QString getSaveFileName(const QString &title, const QString &dir, const QString &filter);
    QString getOpenFileName(const QString &title, const QString &dir, const QString &filter);
};

#endif // DIALOGBRICK_H
