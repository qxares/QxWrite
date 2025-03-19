#ifndef DOCUMENTEDITOR_H
#define DOCUMENTEDITOR_H

#include <QTextEdit>
#include "filedialog.h"
#include "imageplaceholder.h"
#include "imageselector.h"
#include "imagepositioner.h"
#include "imageresizer.h"

class DocumentEditor : public QTextEdit {
    Q_OBJECT
public:
    explicit DocumentEditor(QWidget *parent = nullptr);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void insertImage();
    ImageSelector selector;
    ImagePositioner positioner;
    ImageResizer resizer;
    bool resizing;
};

#endif // DOCUMENTEDITOR_H
