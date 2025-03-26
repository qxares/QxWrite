#ifndef OPENFILEBRICK_H
#define OPENFILEBRICK_H

#include <QObject>

class QTextEdit;
class DialogBrick;

class OpenFileBrick : public QObject {
    Q_OBJECT
public:
    explicit OpenFileBrick(QTextEdit *edit, QObject *parent = nullptr);
    void openFile();
    void setTextEdit(QTextEdit *edit);  // Added

private:
    QTextEdit *m_textEdit;
    DialogBrick *m_dialog;
};

#endif // OPENFILEBRICK_H
