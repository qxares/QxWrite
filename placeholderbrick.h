#ifndef PLACEHOLDERBRICK_H
#define PLACEHOLDERBRICK_H

#include <QObject>
#include <QTextEdit>

class PlaceholderBrick : public QObject {
    Q_OBJECT
public:
    enum ContentType { Table, Image }; // Extensible for future types

    explicit PlaceholderBrick(QTextEdit *textEdit, QObject *parent = nullptr);
    void insertPlaceholder(int position, ContentType type);

private:
    QTextEdit *m_textEdit;
};

#endif // PLACEHOLDERBRICK_H
