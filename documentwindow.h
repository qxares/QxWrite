#ifndef DOCUMENTWINDOW_H
#define DOCUMENTWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include "newfilebrick.h"

class QTextEdit;
class NewFileBrick;
class OpenFileBrick;
class SaveGUIBrick;
class SaveFunctionBrick;

class DocumentWindow : public QWidget {
    Q_OBJECT
public:
    explicit DocumentWindow(QWidget *parent = nullptr);
    ~DocumentWindow();
    QTextEdit* getTextEdit() const;
    void clear();
    void newFile(NewFileBrick::DocType type);

signals:
    void customContextMenuRequested(QMdiSubWindow *subWindow, const QPoint &pos);

protected:
    void closeEvent(QCloseEvent *event);

private:
    QTextEdit *textEdit;
    NewFileBrick *newFileBrick;
    OpenFileBrick *openFileBrick;
    SaveGUIBrick *saveGuiBrick;
    SaveFunctionBrick *saveFunctionBrick;
};

#endif // DOCUMENTWINDOW_H
