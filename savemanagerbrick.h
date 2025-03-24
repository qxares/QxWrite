#ifndef SAVEMANAGERBRICK_H
#define SAVEMANAGERBRICK_H

#include <QObject>
#include <QAction>
#include <QTextEdit>
#include "savefunctionbrick.h"
#include "savehandlerbrick.h"
#include "saveguibrick.h"

class SaveManagerBrick : public QObject {
    Q_OBJECT
public:
    SaveManagerBrick(QTextEdit *edit, QObject *parent = nullptr);
    QAction *saveAction() const;
    QAction *saveAsAction() const;  // Add this

public slots:
    void saveAs();  // Add this

private:
    QTextEdit *m_edit;         // Add this
    SaveFunctionBrick *m_function;  // Add this
    SaveHandlerBrick *m_handler;    // Already included
    SaveGUIBrick *m_gui;       // Already included
    QAction *m_saveAction;     // Already included
    QAction *m_saveAsAction;   // Add this
};

#endif // SAVEMANAGERBRICK_H
