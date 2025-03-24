#ifndef TOOLBARBRICK_H
#define TOOLBARBRICK_H

#include <QObject>
class QToolBar;
class QTextEdit;
class InsertBrick;
class SaveBrick;
class BoldBrick;
class NewFileBrick;
class ItalicBrick;
class OpenFileBrick;
class IconBrick;
class FontBrick;
class ColorBrick;

class ToolBarBrick : public QObject {
    Q_OBJECT
public:
    ToolBarBrick(QToolBar *toolBar, QTextEdit *edit, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile, IconBrick *icon, FontBrick *font, ColorBrick *color, QObject *parent = nullptr);

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
    IconBrick *iconBrick;
    FontBrick *fontBrick;
    ColorBrick *colorBrick;
};

#endif // TOOLBARBRICK_H

