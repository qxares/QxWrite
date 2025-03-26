#ifndef NEWFILEBRICK_H
#define NEWFILEBRICK_H

#include <QObject>
#include <QTextEdit>

class NewFileBrick : public QObject {
    Q_OBJECT
public:
    enum DocType { Note, Document, Sheet };
    NewFileBrick(QTextEdit *edit, QObject *parent = nullptr);
    void newFile(DocType type = Note);  // Default to Note

private:
    QTextEdit *targetEdit;
};

#endif // NEWFILEBRICK_H
