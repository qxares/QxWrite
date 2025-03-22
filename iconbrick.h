#ifndef ICONBRICK_H
#define ICONBRICK_H

#include <QObject>
#include <QIcon>
#include <QMap>

class IconBrick : public QObject {
    Q_OBJECT
public:
    IconBrick(QObject *parent = nullptr);
    QIcon loadIcon(const QString &name);
    void registerIcons();

private:
    QMap<QString, QString> iconMap; // name -> path
    QIcon fallbackIcon;
};

#endif // ICONBRICK_H

