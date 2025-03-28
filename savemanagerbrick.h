#ifndef SAVEMANAGERBRICK_H
#define SAVEMANAGERBRICK_H

#include <QObject>

class QTextEdit;
class SaveFunctionBrick;
class SaveGUIBrick;
class SaveHandlerBrick;

class SaveManagerBrick : public QObject {
    Q_OBJECT
public:
    explicit SaveManagerBrick(QTextEdit *edit, QObject *parent = nullptr);
    void triggerSave();
    void setTextEdit(QTextEdit *edit);  // Added

public slots:
    void validate(); // Added slot for validation

private:
    QTextEdit *m_textEdit;
    SaveFunctionBrick *m_function;
    SaveGUIBrick *m_gui;
    SaveHandlerBrick *m_handler;
};

#endif // SAVEMANAGERBRICK_H
