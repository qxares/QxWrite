#include "savebrick.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QAction>
#include <QDebug>
#include <QDir>
#include "dialogbrick.h"

SaveBrick::SaveBrick(QTextEdit *edit, DialogBrick *dialog, QObject *parent)
    : QObject(parent), targetEdit(edit), dialogBrick(dialog), saveAct(new QAction(tr("Save"), this)) {
    qDebug() << "SaveBrick initialized, target edit:" << edit;
    saveAct->setToolTip(tr("Save the current file"));
    connect(saveAct, &QAction::triggered, this, &SaveBrick::save);
}

void SaveBrick::save() {
    qDebug() << "SaveBrick: save triggered";
    QString fileName = dialogBrick->getSaveFileName(tr("Save File"), QDir::homePath(), tr("Text Files (*.txt)"));
    if (fileName.isEmpty()) {
        qDebug() << "SaveBrick: Save canceled";
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "SaveBrick: Failed to open file:" << fileName;
        return;
    }
    QTextStream out(&file);
    out << targetEdit->toPlainText();
    file.close();
    qDebug() << "File saved:" << fileName;
}

