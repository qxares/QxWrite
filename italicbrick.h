#ifndef ITALICBRICK_H
#define ITALICBRICK_H

#include <QObject>
#include <QTextEdit>
#include <QAction>

class ItalicBrick : public QObject {
    Q_OBJECT
public:
    ItalicBrick(QTextEdit *edit, QObject *parent = nullptr);
    QAction *italicAction() const { return italicAct; }

public slots:
    void toggleItalic();

private:
    QTextEdit *m_edit;
    QAction *italicAct;
};

#endif // ITALICBRICK_H
