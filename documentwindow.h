#ifndef DOCUMENTWINDOW_H
#define DOCUMENTWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>  // Added for QMdiSubWindow
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
    void newFile(NewFileBrick::DocType type);  // Enhanced for QxDocument

signals:
    void customContextMenuRequested(QMdiSubWindow *subWindow, const QPoint &pos);  // Signal for context menu

private:
    QTextEdit *textEdit;
    NewFileBrick *newFileBrick;
    OpenFileBrick *openFileBrick;
};

#endif // DOCUMENTWINDOW_H
