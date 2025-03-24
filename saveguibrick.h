#ifndef SAVEGUIBRICK_H
#define SAVEGUIBRICK_H

#include <QObject>
#include <QString>

class SaveGUIBrick : public QObject {
    Q_OBJECT
public:
    explicit SaveGUIBrick(QObject *parent = nullptr);
    QString getSaveFileName();  // Add this

private:
};

#endif // SAVEGUIBRICK_H
