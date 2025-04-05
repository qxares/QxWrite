#include "resetbrick.h"
#include <QDebug>

ResetBrick::ResetBrick(QObject *parent) : QObject(parent) {
    qDebug() << "ResetBrick initialized";
}

void ResetBrick::resetProcess(QProcess *process) {
    if (!process) {
        qDebug() << "ResetBrick: No process to reset!";
        return;
    }
    terminateProcess(process);
    process->close();  // Close channels
    qDebug() << "ResetBrick: Process reset, state:" << process->state();
}

void ResetBrick::terminateProcess(QProcess *process) {
    if (process->state() != QProcess::NotRunning) {
        process->terminate();
        if (!process->waitForFinished(1000)) {  // 1-second grace period
            process->kill();
            qDebug() << "ResetBrick: Force-killed lingering process";
        } else {
            qDebug() << "ResetBrick: Process terminated gracefully";
        }
    }
}
