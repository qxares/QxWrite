#ifndef DOCUMENTWINDOW_H
#define DOCUMENTWINDOW_H

#include <QWidget>

class QTextEdit;
class NewFileBrick;
class OpenFileBrick;

class DocumentWindow : public QWidget {
    Q_OBJECT
public:
    explicit DocumentWindow(QWidget *parent = nullptr);
    ~DocumentWindow();
    QTextEdit* getTextEdit() const;
    void clear();

private:
    QTextEdit *textEdit;
    NewFileBrick *newFileBrick;
    OpenFileBrick *openFileBrick;
};

#endif // DOCUMENTWINDOW_H
