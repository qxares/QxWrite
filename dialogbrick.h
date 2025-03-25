#ifndef DIALOGBRICK_H
#define DIALOGBRICK_H

#include <QObject>
#include <QString>
#include <QWidget>

class DialogBrick : public QObject {
    Q_OBJECT
public:
    explicit DialogBrick(QObject *parent = nullptr);
    QString getOpenFileName(QWidget *parent, const QString &caption = "", const QString &dir = "", const QString &filter = "");

private:
    QString lastDir;
};

#endif // DIALOGBRICK_H
