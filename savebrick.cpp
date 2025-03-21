#include "savebrick.h"
#include "dialogbrick.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QDebug>

SaveBrick::SaveBrick(QTextEdit *edit, DialogBrick *dialog, QObject *parent)
    : QObject(parent), targetEdit(edit), dialogBrick(dialog) {
    qDebug() << "SaveBrick initialized, target edit:" << edit;
}

void SaveBrick::save() {
    qDebug() << "SaveBrick: save triggered";
    QString fileName = dialogBrick->getSaveFileName(tr("Save File"), QDir::homePath(), "");
    if (fileName.isEmpty()) return;

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

