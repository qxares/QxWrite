#ifndef BOLDBRICK_H
#define BOLDBRICK_H

#include <QObject>
#include <QTextEdit>

class BoldBrick : public QObject {
    Q_OBJECT
public:
    explicit BoldBrick(QTextEdit *edit = nullptr, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *edit);

public slots:
    void applyBold();
    void resetTextEdit(); // Add this

private:
    QTextEdit *m_textEdit;
};

#endif // BOLDBRICK_H
