#ifndef DOCUMENTHANDLERBRICK_H
#define DOCUMENTHANDLERBRICK_H

#include <QObject>
#include <QList>
#include <QMdiSubWindow>
#include "newfilebrick.h"
#include "documentwindow.h"

class QMdiArea;
class OpenFileBrick;
class QTextEdit;

class DocumentHandlerBrick : public QObject {
    Q_OBJECT
public:
    explicit DocumentHandlerBrick(QWidget *parent = nullptr);
    QTextEdit* newDocument(NewFileBrick::DocType type);
    void openDocument(OpenFileBrick *openFileBrick);
    QTextEdit* getActiveTextEdit(); // New method to get active window's QTextEdit

private slots:
    void showContextMenu(QMdiSubWindow *subWindow, const QPoint &pos);
    void moveCascade(QMdiSubWindow *subWindow);

private:
    void cascadeWindows(NewFileBrick::DocType type);
    QMdiArea *mdiArea;
    QList<QMdiSubWindow*> documentWindows;
    QList<QMdiSubWindow*> noteWindows;
    QList<QMdiSubWindow*> sheetWindows;
};

#endif // DOCUMENTHANDLERBRICK_H
