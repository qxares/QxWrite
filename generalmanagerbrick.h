#ifndef GENERALMANAGERBRICK_H
#define GENERALMANAGERBRICK_H

#include <QObject>

class QMenuBar;
class InsertBrick;
class SaveBrick;

class GeneralManagerBrick : public QObject {
    Q_OBJECT
public:
    explicit GeneralManagerBrick(QObject *parent = nullptr);
    void initBricks();

private:
    QMenuBar *menuBar;
    InsertBrick *insertBrick;
    SaveBrick *saveBrick;
};

#endif // GENERALMANAGERBRICK_H
