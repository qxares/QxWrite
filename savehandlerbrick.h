#ifndef SAVEHANDLERBRICK_H
#define SAVEHANDLERBRICK_H

#include <QObject>

class SaveFunctionBrick;
class SaveGUIBrick;

class SaveHandlerBrick : public QObject {
    Q_OBJECT
public:
    explicit SaveHandlerBrick(SaveFunctionBrick *saveFunction, SaveGUIBrick *saveGui, QObject *parent = nullptr);
    void handleSave();

private:
    SaveFunctionBrick *m_saveFunction;
    SaveGUIBrick *m_saveGui;
};

#endif // SAVEHANDLERBRICK_H
