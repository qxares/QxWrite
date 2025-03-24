#ifndef DOCUMENTEDITOR_H
#define DOCUMENTEDITOR_H

#include <QWidget>
#include "imagescenemanager.h"

class QTextEdit;
class QGraphicsView;

class DocumentEditor : public QWidget {
    Q_OBJECT
public:
    DocumentEditor(ImageSceneManager *sceneManager, QWidget *parent = nullptr);
    bool acceptRichText() const;
    QTextEdit* getTextEdit() const;

private:
    ImageSceneManager *sceneManager;
    QTextEdit *textEdit;
    QGraphicsView *view;
};

#endif // DOCUMENTEDITOR_H
