#ifndef DOCUMENTHANDLERBRICK_H
#define DOCUMENTHANDLERBRICK_H

#include <QObject>
#include <QList>  // For QList<QMdiSubWindow*>
#include <QMdiSubWindow>  // Added for QMdiSubWindow
#include "newfilebrick.h"
#include "documentwindow.h"

class QMdiArea;
class OpenFileBrick;

class DocumentHandlerBrick : public QObject {
    Q_OBJECT
public:
    explicit DocumentHandlerBrick(QWidget *parent = nullptr);
    void newDocument(NewFileBrick::DocType type);
    void openDocument(OpenFileBrick *openFileBrick); // New method for opening files

private:
    void cascadeWindows(NewFileBrick::DocType type); // Cascade windows of a specific type
    QMdiArea *mdiArea;  // Manage subwindows here
    QList<QMdiSubWindow*> documentWindows; // QxDocuments
    QList<QMdiSubWindow*> noteWindows;     // QxNotes
    QList<QMdiSubWindow*> sheetWindows;    // QxSheets
};

#endif // DOCUMENTHANDLERBRICK_H
