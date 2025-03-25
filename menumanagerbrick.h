#ifndef MENUMANAGERBRICK_H
#define MENUMANAGERBRICK_H

#include <QObject>

class QMenuBar;
class IconBrick;

class MenuManagerBrick : public QObject {
    Q_OBJECT
public:
    explicit MenuManagerBrick(QWidget *parent = nullptr);
    QMenuBar* getMenuBar();

private:
    void setupMenus();
    QMenuBar *menuBar;
    IconBrick *iconBrick;
};

#endif // MENUMANAGERBRICK_H
