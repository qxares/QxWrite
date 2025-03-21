#ifndef ICONBRICK_H
#define ICONBRICK_H

#include <QObject>
#include <QIcon>
#include <QMap>

class IconBrick : public QObject {
    Q_OBJECT
public:
    explicit IconBrick(QObject *parent = nullptr);
    QIcon getIcon(const QString &name);

private:
    QMap<QString, QIcon> iconCache;
};

#endif // ICONBRICK_H
