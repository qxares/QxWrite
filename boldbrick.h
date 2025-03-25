#ifndef BOLDBRICK_H
#define BOLDBRICK_H

#include <QObject>
#include <QTextEdit>

class BoldBrick : public QObject {
    Q_OBJECT
public:
    explicit BoldBrick(QTextEdit *edit, QObject *parent = nullptr);
    void applyBold();

private:
    QTextEdit *m_textEdit;
};

#endif // BOLDBRICK_H
