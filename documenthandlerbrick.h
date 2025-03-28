#ifndef DOCUMENTHANDLERBRICK_H
#define DOCUMENTHANDLERBRICK_H

#include <QObject>
#include <QList>  // For QList<QMdiSubWindow*>
#include <QMdiSubWindow>  // Added for QMdiSubWindow
#include "newfilebrick.h"
#include "documentwindow.h"

class QMdiArea;
class OpenFileBrick;
class QTextEdit;

class DocumentHandlerBrick : public QObject {
    Q_OBJECT
public:
    explicit DocumentHandlerBrick(QWidget *parent = nullptr);
    QTextEdit* newDocument(NewFileBrick::DocType type); // Changed to return QTextEdit*
    void openDocument(OpenFileBrick *openFileBrick); // New method for opening files

private slots:
    void showContextMenu(QMdiSubWindow *subWindow, const QPoint &pos);  // Handle context menu
    void moveCascade(QMdiSubWindow *subWindow);  // Move the cascade

private:
    void cascadeWindows(NewFileBrick::DocType type); // Cascade windows of a specific type
    QMdiArea *mdiArea;  // Manage subwindows here
    QList<QMdiSubWindow*> documentWindows; // QxDocuments
    QList<QMdiSubWindow*> noteWindows;     // QxNotes
    QList<QMdiSubWindow*> sheetWindows;    // QxSheets
};

#endif // DOCUMENTHANDLERBRICK_H
