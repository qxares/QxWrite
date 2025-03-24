#include "savefunctionbrick.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

SaveFunctionBrick::SaveFunctionBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), m_edit(edit) {}

void SaveFunctionBrick::save(const QString &fileName) {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << m_edit->toHtml();
        file.close();
        qDebug() << "SaveFunctionBrick: File saved:" << fileName;
    }
}
