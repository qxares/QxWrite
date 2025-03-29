#ifndef DOCUMENTWINDOW_H
#define DOCUMENTWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include "newfilebrick.h"

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
    void newFile(NewFileBrick::DocType type);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override; // Added for mouse event handling

signals:
    void customContextMenuRequested(QMdiSubWindow *subWindow, const QPoint &pos);

private:
    QTextEdit *textEdit;
    NewFileBrick *newFileBrick;
    OpenFileBrick *openFileBrick;
};

#endif // DOCUMENTWINDOW_H
