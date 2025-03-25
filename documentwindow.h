#ifndef DOCUMENTWINDOW_H
#define DOCUMENTWINDOW_H

#include <QMainWindow>

class QTextEdit;
class OpenFileBrick;

class DocumentWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit DocumentWindow(QWidget *parent = nullptr);

private:
    void setupUI();
    QTextEdit *textEdit;
    OpenFileBrick *openFileBrick;
};

#endif // DOCUMENTWINDOW_H
