#ifndef DOCUMENTEDITOR_H
#define DOCUMENTEDITOR_H

#include <QTextEdit>
#include <QMap>
#include <QImage>

class DocumentEditor : public QTextEdit {
    Q_OBJECT
public:
    explicit DocumentEditor(QWidget *parent = nullptr);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    void insertImage();
};

#endif // DOCUMENTEDITOR_H
