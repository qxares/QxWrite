#ifndef SAVEFUNCTIONBRICK_H
#define SAVEFUNCTIONBRICK_H

#include <QObject>
#include <QString>

class QTextEdit;

class SaveFunctionBrick : public QObject {
    Q_OBJECT
public:
    explicit SaveFunctionBrick(QTextEdit *edit, QObject *parent = nullptr);
    void save(const QString &fileName);
    void setTextEdit(QTextEdit *edit);

private:
    QTextEdit *m_textEdit;
};

#endif // SAVEFUNCTIONBRICK_H
