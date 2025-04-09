#ifndef HTMLFILEBRICK_H
#define HTMLFILEBRICK_H

#include <QObject>
#include <QTextEdit>

class HtmlFileBrick : public QObject {
    Q_OBJECT
public:
    explicit HtmlFileBrick(QTextEdit *textEdit, QObject *parent = nullptr);
    void setTextEdit(QTextEdit *edit);
    QString importFile(const QString &filePath);
    void exportFile(const QString &filePath);

private:
    QTextEdit *textEdit;
};

#endif // HTMLFILEBRICK_H
