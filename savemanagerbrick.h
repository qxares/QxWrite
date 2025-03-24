#ifndef SAVEMANAGERBRICK_H
#define SAVEMANAGERBRICK_H

#include <QObject>
#include <QAction>
#include "savehandlerbrick.h"

class SaveManagerBrick : public QObject {
    Q_OBJECT
public:
    SaveManagerBrick(QTextEdit *edit, QObject *parent = nullptr);
    QAction *saveAction() const;

private:
    SaveGUIBrick *m_gui;       // Add this
    QAction *m_saveAction;     // Add this
};

#endif // SAVEMANAGERBRICK_H
