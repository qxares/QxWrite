#ifndef BOLDBRICK_H
#define BOLDBRICK_H

#include <QObject>
#include <QTextEdit>
#include <QAction>

class BoldBrick : public QObject {
    Q_OBJECT
public:
    BoldBrick(QTextEdit *edit, QObject *parent = nullptr);
    QAction *boldAction() const { return boldAct; }

public slots:
    void toggleBold();

private:
    QTextEdit *m_edit;
    QAction *boldAct;
};

#endif // BOLDBRICK_H
