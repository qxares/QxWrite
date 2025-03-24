#ifndef SAVEGUIBRICK_H
#define SAVEGUIBRICK_H

#include <QObject>
#include <QAction>

class SaveGUIBrick : public QObject {
    Q_OBJECT
public:
    SaveGUIBrick(QObject *parent = nullptr);
    QAction *saveAction() const { return m_saveAction; }

private:
    QAction *m_saveAction;
};

#endif // SAVEGUIBRICK_H
