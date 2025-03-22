#ifndef SAVEBRICK_H
#define SAVEBRICK_H

#include <QObject>
class QTextEdit;
class DialogBrick;
class QAction;

class SaveBrick : public QObject {
    Q_OBJECT
public:
    SaveBrick(QTextEdit *edit, DialogBrick *dialog, QObject *parent = nullptr);
    QAction* getSaveAction() const { return saveAct; }

public slots:
    void save();

private:
    QTextEdit *targetEdit;
    DialogBrick *dialogBrick;
    QAction *saveAct;
};

#endif // SAVEBRICK_H

