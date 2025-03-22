#ifndef MENUMANAGERBRICK_H
#define MENUMANAGERBRICK_H

#include <QObject>
class QMenuBar;
class QTextEdit;
class QAction;
class InsertBrick;
class SaveBrick;
class BoldBrick;
class NewFileBrick;
class ItalicBrick;
class OpenFileBrick;
class FontBrick;
class ColorBrick;

class MenuManagerBrick : public QObject {
    Q_OBJECT
public:
    MenuManagerBrick(QMenuBar *menuBar, QTextEdit *edit, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile, FontBrick *font, ColorBrick *color, QObject *parent = nullptr);

private slots:
    void updateToggleStates();

private:
    QMenuBar *menuBar;
    QTextEdit *targetEdit;
    InsertBrick *insertBrick;
    SaveBrick *saveBrick;
    BoldBrick *boldBrick;
    NewFileBrick *newFileBrick;
    ItalicBrick *italicBrick;
    OpenFileBrick *openFileBrick;
    FontBrick *fontBrick;
    ColorBrick *colorBrick;
    QAction *boldAct;
    QAction *italicAct;
};

#endif // MENUMANAGERBRICK_H

