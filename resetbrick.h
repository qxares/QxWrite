#ifndef RESETBRICK_H
#define RESETBRICK_H

#include <QObject>
#include <QProcess>

class ResetBrick : public QObject {
    Q_OBJECT
public:
    explicit ResetBrick(QObject *parent = nullptr);
    void resetProcess(QProcess *process);  // Reset a given QProcess

private:
    void terminateProcess(QProcess *process);  // Terminate and clean up
};

#endif // RESETBRICK_H
