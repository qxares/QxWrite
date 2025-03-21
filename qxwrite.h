#ifndef QXWRITE_H
#define QXWRITE_H

#include <QMainWindow>
#include <QTextEdit>

class GeneralManagerBrick;

class QxWrite : public QMainWindow {
    Q_OBJECT
public:
    explicit QxWrite(QWidget *parent = nullptr);
    ~QxWrite();

private:
    QTextEdit *textEdit; // Temporary until DocumentBrick
    GeneralManagerBrick *manager;
};

#endif // QXWRITE_H
