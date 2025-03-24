#ifndef BOLDBRICK_H
#define BOLDBRICK_H

#include <QObject>

class QTextEdit;

class BoldBrick : public QObject {
    Q_OBJECT
public:
    explicit BoldBrick(QTextEdit *edit, QObject *parent = nullptr);

public slots:
    void toggleBold(bool checked);

signals:
    void boldToggled(bool checked);

private:
    QTextEdit *targetEdit;
};

#endif // BOLDBRICK_H
