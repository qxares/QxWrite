#include "savefunctionbrick.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QDebug>

SaveFunctionBrick::SaveFunctionBrick(QTextEdit *edit, QObject *parent) 
    : QObject(parent), m_textEdit(edit) {
    qDebug() << "SaveFunctionBrick initialized";
}

void SaveFunctionBrick::save(const QString &fileName) {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << m_textEdit->toPlainText();
        file.close();
        qDebug() << "SaveFunctionBrick: Saved to" << fileName;
    } else {
        qDebug() << "SaveFunctionBrick: Failed to save to" << fileName;
    }
}
