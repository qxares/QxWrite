#ifndef SAVEBRICK_H
#define SAVEBRICK_H

#include <QObject>
class QTextEdit;
class DialogBrick;

class SaveBrick : public QObject {
    Q_OBJECT
public:
    SaveBrick(QTextEdit *edit, DialogBrick *dialog, QObject *parent = nullptr);
    void save();

private:
    QTextEdit *targetEdit;
    DialogBrick *dialogBrick;
};

#endif // SAVEBRICK_H
