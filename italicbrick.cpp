#include "italicbrick.h"
#include <QTextEdit>
#include <QTextCharFormat>
#include <QDebug>

ItalicBrick::ItalicBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), targetEdit(edit) {
    qDebug() << "ItalicBrick initialized, target edit:" << targetEdit;
}

void ItalicBrick::toggleItalic(bool checked) {
    qDebug() << "ItalicBrick: toggleItalic triggered, checked:" << checked;
    if (!targetEdit) {
        qDebug() << "No target QTextEdit provided!";
        return;
    }
    QTextCursor cursor = targetEdit->textCursor();
    QTextCharFormat format;
    format.setFontItalic(checked);
    cursor.mergeCharFormat(format);
    targetEdit->setTextCursor(cursor);
    emit italicToggled(checked);
}
