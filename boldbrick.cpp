#include "boldbrick.h"
#include <QTextEdit>
#include <QTextCharFormat>
#include <QDebug>

BoldBrick::BoldBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), targetEdit(edit) {
    qDebug() << "BoldBrick initialized, target edit:" << targetEdit;
}

void BoldBrick::toggleBold() {
    qDebug() << "BoldBrick: toggleBold triggered";
    if (!targetEdit) {
        qDebug() << "No target QTextEdit provided!";
        return;
    }
    QTextCursor cursor = targetEdit->textCursor();
    QTextCharFormat format;
    format.setFontWeight(cursor.charFormat().fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
    cursor.mergeCharFormat(format);
    targetEdit->setTextCursor(cursor);
}
