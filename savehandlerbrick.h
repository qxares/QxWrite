#ifndef SAVEHANDLERBRICK_H
#define SAVEHANDLERBRICK_H

#include <QObject>
#include "savefunctionbrick.h"
#include "dialogbrick.h"

class SaveHandlerBrick : public QObject {
    Q_OBJECT
public:
    SaveHandlerBrick(QTextEdit *textEdit, SaveFunctionBrick *function, DialogBrick *dialog, QObject *parent = nullptr);

public slots:
    void handleSave();

private:
    QTextEdit *m_textEdit;
    SaveFunctionBrick *m_saveFunction;
    DialogBrick *m_dialog;
};

#endif // SAVEHANDLERBRICK_H
