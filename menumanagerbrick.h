#ifndef MENUMANAGERBRICK_H
#define MENUMANAGERBRICK_H

#include <QObject>

class QMenuBar;
class QAction;
class InsertBrick;
class SaveBrick;
class BoldBrick;
class NewFileBrick;
class ItalicBrick;
class OpenFileBrick;

class MenuManagerBrick : public QObject {
    Q_OBJECT
public:
    explicit MenuManagerBrick(QMenuBar *bar, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile, QObject *parent = nullptr);
    void setupMenus();

private slots:
    void updateToggleStates();

private:
    QMenuBar *menuBar;
    InsertBrick *insertBrick;
    SaveBrick *saveBrick;
    BoldBrick *boldBrick;
    NewFileBrick *newFileBrick;
    ItalicBrick *italicBrick;
    OpenFileBrick *openFileBrick;
    QAction *boldAction;
    QAction *italicAction;
};

#endif // MENUMANAGERBRICK_H
