#ifndef DOCUMENTWINDOW_H
#define DOCUMENTWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include "newfilebrick.h"
#include "imagescenemanager.h" // Added for ImageSceneManager

class QTextEdit;
class NewFileBrick;
class OpenFileBrick;

class DocumentWindow : public QWidget {
    Q_OBJECT
public:
    explicit DocumentWindow(ImageSceneManager *sceneManager, QWidget *parent = nullptr); // Updated constructor
    ~DocumentWindow();
    QTextEdit* getTextEdit() const;
    void clear();
    void newFile(NewFileBrick::DocType type);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void customContextMenuRequested(QMdiSubWindow *subWindow, const QPoint &pos);

private:
    QTextEdit *textEdit;
    NewFileBrick *newFileBrick;
    OpenFileBrick *openFileBrick;
    ImageSceneManager *sceneManager; // Added to store the pointer
};

#endif // DOCUMENTWINDOW_H
