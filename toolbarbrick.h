#ifndef TOOLBARBRICK_H
#define TOOLBARBRICK_H

#include <QObject>

class QToolBar;
class InsertBrick;
class SaveBrick;
class BoldBrick;
class NewFileBrick;

class ToolBarBrick : public QObject {
    Q_OBJECT
public:
    explicit ToolBarBrick(QToolBar *bar, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, QObject *parent = nullptr);
    void setupToolBar();

private:
    QToolBar *toolBar;
    InsertBrick *insertBrick;
    SaveBrick *saveBrick;
    BoldBrick *boldBrick;
    NewFileBrick *newFileBrick;
};

#endif // TOOLBARBRICK_H
