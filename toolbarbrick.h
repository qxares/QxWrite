#ifndef TOOLBARBRICK_H
#define TOOLBARBRICK_H

#include <QObject>
#include <QTextEdit>
#include <QTextCursor>

class QToolBar;
class QAction;
class InsertBrick;
class SaveBrick;
class BoldBrick;
class NewFileBrick;
class ItalicBrick;
class OpenFileBrick;

class ToolBarBrick : public QObject {
    Q_OBJECT
public:
    explicit ToolBarBrick(QToolBar *bar, QTextEdit *edit, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile, QObject *parent = nullptr);
    void setupToolBar();

private slots:
    void updateToggleStates();

private:
    QToolBar *toolBar;
    QTextEdit *targetEdit;
    InsertBrick *insertBrick;
    SaveBrick *saveBrick;
    BoldBrick *boldBrick;
    NewFileBrick *newFileBrick;
    ItalicBrick *italicBrick;
    OpenFileBrick *openFileBrick;
    QAction *boldAction;
    QAction *italicAction;
};

#endif // TOOLBARBRICK_H
