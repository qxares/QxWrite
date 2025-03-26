#ifndef SAVEGUIBRICK_H
#define SAVEGUIBRICK_H

#include <QObject>

class QTextEdit;
class DialogBrick;

class SaveGUIBrick : public QObject {
    Q_OBJECT
public:
    explicit SaveGUIBrick(QTextEdit *edit, QObject *parent = nullptr);
    QString getSaveFileName();
    void setTextEdit(QTextEdit *edit);  // Added

private:
    QTextEdit *m_textEdit;
    DialogBrick *m_dialog;
};

#endif // SAVEGUIBRICK_H
