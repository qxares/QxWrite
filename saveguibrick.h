#ifndef SAVEGUIBRICK_H
#define SAVEGUIBRICK_H

#include <QObject>
#include <QString>

class QTextEdit;
class DialogBrick;

class SaveGUIBrick : public QObject {
    Q_OBJECT
public:
    explicit SaveGUIBrick(QTextEdit *edit, QObject *parent = nullptr);
    QString getSaveFileName(bool saveAs = false);
    void setTextEdit(QTextEdit *edit);

private:
    QTextEdit *m_textEdit;
    DialogBrick *m_dialog;
    QString m_lastFileName; // Track last saved file
};

#endif // SAVEGUIBRICK_H
