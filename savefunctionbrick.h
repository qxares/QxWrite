#ifndef SAVEFUNCTIONBRICK_H
#define SAVEFUNCTIONBRICK_H

#include <QObject>
#include <QTextEdit>

class SaveFunctionBrick : public QObject {
    Q_OBJECT
public:
    SaveFunctionBrick(QTextEdit *edit, QObject *parent = nullptr);
    void save(const QString &fileName);

private:
    QTextEdit *m_edit;
};

#endif // SAVEFUNCTIONBRICK_H
