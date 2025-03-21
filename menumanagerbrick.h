#ifndef MENUMANAGERBRICK_H
#define MENUMANAGERBRICK_H

#include <QObject>

class QMenuBar;
class InsertBrick;
class SaveBrick;
class BoldBrick;
class NewFileBrick;
class ItalicBrick;

class MenuManagerBrick : public QObject {
    Q_OBJECT
public:
    explicit MenuManagerBrick(QMenuBar *bar, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, QObject *parent = nullptr);
    void setupMenus();

private:
    QMenuBar *menuBar;
    InsertBrick *insertBrick;
    SaveBrick *saveBrick;
    BoldBrick *boldBrick;
    NewFileBrick *newFileBrick;
    ItalicBrick *italicBrick;
};

#endif // MENUMANAGERBRICK_H
