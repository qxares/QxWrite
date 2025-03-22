#ifndef ITALICBRICK_H
#define ITALICBRICK_H

#include <QObject>

class QTextEdit;

class ItalicBrick : public QObject {
    Q_OBJECT
public:
    explicit ItalicBrick(QTextEdit *edit, QObject *parent = nullptr);

public slots:
    void toggleItalic(bool checked);

signals:
    void italicToggled(bool checked);

private:
    QTextEdit *targetEdit;
};

#endif // ITALICBRICK_H
