#ifndef MAINWINDOWBRICK_H
#define MAINWINDOWBRICK_H

#include <QMainWindow>
#include <QTextEdit>

class MainWindowBrick : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindowBrick(QWidget *parent = nullptr);
    ~MainWindowBrick();

    QTextEdit* getTextEdit() const { return textEdit; }

private:
    QTextEdit *textEdit;
};

#endif // MAINWINDOWBRICK_H
