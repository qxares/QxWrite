#ifndef SAVEMANAGERBRICK_H
#define SAVEMANAGERBRICK_H

#include <QObject>
#include "saveguibrick.h"
#include "savehandlerbrick.h"

class SaveManagerBrick : public QObject {
    Q_OBJECT
public:
    SaveManagerBrick(QTextEdit *textEdit, QObject *parent = nullptr);
    QAction *saveAction() const;

private:
    SaveGUIBrick *m_gui;
    SaveHandlerBrick *m_handler;
};

#endif // SAVEMANAGERBRICK_H
