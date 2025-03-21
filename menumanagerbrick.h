#ifndef MENUMANAGERBRICK_H
#define MENUMANAGERBRICK_H

#include <QObject>

class QMenuBar;
class InsertBrick;
class SaveBrick;

class MenuManagerBrick : public QObject {
    Q_OBJECT
public:
    explicit MenuManagerBrick(QMenuBar *bar, InsertBrick *insert, SaveBrick *save, QObject *parent = nullptr);
    void setupMenus();

private:
    QMenuBar *menuBar;
    InsertBrick *insertBrick;
    SaveBrick *saveBrick;
};

#endif // MENUMANAGERBRICK_H
