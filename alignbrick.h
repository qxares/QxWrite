#ifndef ALIGNBRICK_H
#define ALIGNBRICK_H

#include <QObject>
#include <QTextEdit>
#include <QTextBlockFormat>

class AlignBrick : public QObject {
    Q_OBJECT
public:
    enum Alignment { AlignLeft, AlignCenter, AlignRight };

    explicit AlignBrick(QTextEdit *edit, Alignment alignment, QObject *parent = nullptr);

public slots:
    void alignText();

private:
    QTextEdit *targetEdit;
    Alignment alignType;
};

#endif // ALIGNBRICK_H
