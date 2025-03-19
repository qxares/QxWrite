#ifndef DOCUMENTWINDOW_H
#define DOCUMENTWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include "imagescenemanager.h"

class DocumentWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit DocumentWindow(ImageSceneManager *sceneManager, QWidget *parent = nullptr);
    QTextEdit *getTextEdit() const { return textEdit; }

private:
    QTextEdit *textEdit;
    ImageSceneManager *sceneManager;
};

#endif // DOCUMENTWINDOW_H
