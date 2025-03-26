#ifndef DOCUMENTHANDLERBRICK_H
#define DOCUMENTHANDLERBRICK_H

#include <QObject>
#include "newfilebrick.h"
#include "documentwindow.h"

class QMdiArea;

class DocumentHandlerBrick : public QObject {
    Q_OBJECT
public:
    explicit DocumentHandlerBrick(QWidget *parent = nullptr);
    void newDocument(NewFileBrick::DocType type);

private:
    QMdiArea *mdiArea;  // Manage subwindows here
};

#endif // DOCUMENTHANDLERBRICK_H
