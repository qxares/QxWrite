#ifndef FONTBRICK_H
#define FONTBRICK_H

#include <QObject>
class QTextEdit;
class QAction;

class FontBrick : public QObject {
    Q_OBJECT
public:
    FontBrick(QTextEdit *edit, QObject *parent = nullptr);
    QAction* getFontAction() const { return fontAct; }

public slots:
    void showFontDialog();

private:
    QTextEdit *targetEdit;
    QAction *fontAct;
};

#endif // FONTBRICK_H

