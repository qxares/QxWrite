#include "italicbrick.h"
#include <QTextEdit>
#include <QTextCharFormat>
#include <QDebug>

ItalicBrick::ItalicBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), targetEdit(edit) {
    qDebug() << "ItalicBrick initialized, target edit:" << targetEdit;
}

void ItalicBrick::toggleItalic() {
    qDebug() << "ItalicBrick: toggleItalic triggered";
    if (!targetEdit) {
        qDebug() << "No target QTextEdit provided!";
        return;
    }
    QTextCursor cursor = targetEdit->textCursor();
    QTextCharFormat format;
    format.setFontItalic(!cursor.charFormat().fontItalic());
    cursor.mergeCharFormat(format);
    targetEdit->setTextCursor(cursor);
}
