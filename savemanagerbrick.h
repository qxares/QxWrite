#ifndef SAVEMANAGERBRICK_H
#define SAVEMANAGERBRICK_H

#include <QObject>
#include <QString>

class QTextEdit;
class SaveFunctionBrick;
class SaveGUIBrick;
class SaveHandlerBrick;

class SaveManagerBrick : public QObject {
    Q_OBJECT
public:
    explicit SaveManagerBrick(QTextEdit *edit, QObject *parent = nullptr);
    ~SaveManagerBrick(); // Added destructor
    void setTextEdit(QTextEdit *edit);

public slots:
    bool triggerSave();  // Changed to return bool
    void triggerSaveAs();

private:
    QTextEdit *m_textEdit;
    SaveFunctionBrick *m_function;
    SaveGUIBrick *m_gui;
    SaveHandlerBrick *m_handler;
    QString m_lastSavedFileName; // Track last saved file per window
};

#endif // SAVEMANAGERBRICK_H
