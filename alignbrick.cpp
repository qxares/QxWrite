#include "alignbrick.h"
#include <QTextCursor>
#include <QDebug>

AlignBrick::AlignBrick(QTextEdit *edit, Alignment align, QObject *parent)
    : QObject(parent), textEdit(edit), alignment(align) {
    qDebug() << "AlignBrick initialized, alignment:" << align;
}

void AlignBrick::align() {
    if (!textEdit) {
        qDebug() << "AlignBrick: No textEdit to align!";
        return;
    }
    QTextBlockFormat format;
    switch (alignment) {
    case AlignLeft:
        format.setAlignment(Qt::AlignLeft);
        break;
    case AlignCenter:
        format.setAlignment(Qt::AlignCenter);
        break;
    case AlignRight:
        format.setAlignment(Qt::AlignRight);
        break;
    }
    QTextCursor cursor = textEdit->textCursor();
    cursor.mergeBlockFormat(format);
    textEdit->setTextCursor(cursor);
    qDebug() << "AlignBrick: Applied alignment:" << alignment;
}
