#ifndef TOOLBARBRICK_H
#define TOOLBARBRICK_H

#include <QObject>
#include "insertbrick.h"
#include "savemanagerbrick.h"
#include "boldbrick.h"
#include "newfilebrick.h"
#include "italicbrick.h"
#include "openfilebrick.h"
#include "iconbrick.h"
#include "fontbrick.h"
#include "colorbrick.h"

class QToolBar;
class QTextEdit;

class ToolBarBrick : public QObject {
    Q_OBJECT
public:
    ToolBarBrick(QToolBar *toolBar, QTextEdit *edit,
                 InsertBrick *insertBrick, SaveManagerBrick *saveManagerBrick,
                 BoldBrick *boldBrick, NewFileBrick *newFileBrick,
                 ItalicBrick *italicBrick, OpenFileBrick *openFileBrick,
                 IconBrick *iconBrick, FontBrick *fontBrick,
                 ColorBrick *colorBrick, QObject *parent = nullptr);
    ~ToolBarBrick() override;  // Add this
};

#endif // TOOLBARBRICK_H
