#include "alignbrick.h"
#include <QDebug>

AlignBrick::AlignBrick(QTextEdit *edit, Alignment alignment, QObject *parent)
    : QObject(parent), targetEdit(edit), alignType(alignment) {
    qDebug() << "AlignBrick initialized for" << (alignType == AlignLeft ? "left" : alignType == AlignCenter ? "center" : "right")
             << "alignment, target edit:" << targetEdit;
}

void AlignBrick::alignText() {
    if (!targetEdit) {
        qDebug() << "AlignBrick: No target edit set, cannot align text";
        return;
    }

    QTextCursor cursor = targetEdit->textCursor();
    QTextBlockFormat blockFormat = cursor.blockFormat();

    switch (alignType) {
    case AlignLeft:
        blockFormat.setAlignment(Qt::AlignLeft);
        qDebug() << "AlignBrick: Applying left alignment";
        break;
    case AlignCenter:
        blockFormat.setAlignment(Qt::AlignCenter);
        qDebug() << "AlignBrick: Applying center alignment";
        break;
    case AlignRight:
        blockFormat.setAlignment(Qt::AlignRight);
        qDebug() << "AlignBrick: Applying right alignment";
        break;
    }

    cursor.setBlockFormat(blockFormat);
    targetEdit->setTextCursor(cursor);
}
