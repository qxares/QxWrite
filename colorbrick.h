#ifndef COLORBRICK_H
#define COLORBRICK_H

#include <QObject>
#include <QColor>
class QTextEdit;
class QAction;

class ColorBrick : public QObject {
    Q_OBJECT
public:
    ColorBrick(QTextEdit *edit, QObject *parent = nullptr);
    QAction* getColorAction() const { return colorAct; }

public slots:
    void showColorDialog();

private:
    QTextEdit *targetEdit;
    QAction *colorAct;
    QColor currentColor;
};

#endif // COLORBRICK_H

