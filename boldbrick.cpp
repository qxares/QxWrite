#include "boldbrick.h"
#include <QTextEdit>
#include <QTextCharFormat>
#include <QDebug>

BoldBrick::BoldBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), targetEdit(edit) {
    qDebug() << "BoldBrick initialized, target edit:" << targetEdit;
}

void BoldBrick::toggleBold(bool checked) {
    qDebug() << "BoldBrick: toggleBold triggered, checked:" << checked;
    if (!targetEdit) {
        qDebug() << "No target QTextEdit provided!";
        return;
    }
    QTextCursor cursor = targetEdit->textCursor();
    QTextCharFormat format;
    format.setFontWeight(checked ? QFont::Bold : QFont::Normal);
    cursor.mergeCharFormat(format);
    targetEdit->setTextCursor(cursor);
    emit boldToggled(checked);
}
