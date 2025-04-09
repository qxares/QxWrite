#include "listbrick.h"
#include <QTextCursor>
#include <QTextList>
#include <QTextBlock>
#include <QDebug>

ListBrick::ListBrick(QTextEdit *edit, QObject *parent) : QObject(parent), targetEdit(edit) {
    qDebug() << "ListBrick initialized, target edit:" << targetEdit;
}

void ListBrick::setTextEdit(QTextEdit *edit) {
    targetEdit = edit;
    qDebug() << "ListBrick: TextEdit updated to:" << targetEdit;
}

void ListBrick::toggleBullets() {
    if (!targetEdit) {
        qDebug() << "ListBrick: No target edit set for bullets";
        return;
    }

    QTextCursor cursor = targetEdit->textCursor();
    QTextList *currentList = cursor.currentList();

    if (currentList && currentList->format().style() == QTextListFormat::ListDisc) {
        // Remove bullets
        QTextBlock block = cursor.block();
        currentList->remove(block);
        qDebug() << "ListBrick: Bullets removed from block at position" << block.position();
    } else {
        // Add bullets
        cursor.createList(QTextListFormat::ListDisc);
        qDebug() << "ListBrick: Bullets added at cursor position" << cursor.position();
    }
    targetEdit->setTextCursor(cursor);
}

void ListBrick::toggleNumbering() {
    if (!targetEdit) {
        qDebug() << "ListBrick: No target edit set for numbering";
        return;
    }

    QTextCursor cursor = targetEdit->textCursor();
    QTextList *currentList = cursor.currentList();

    if (currentList && currentList->format().style() == QTextListFormat::ListDecimal) {
        // Remove numbering
        QTextBlock block = cursor.block();
        currentList->remove(block);
        qDebug() << "ListBrick: Numbering removed from block at position" << block.position();
    } else {
        // Add numbering
        cursor.createList(QTextListFormat::ListDecimal);
        qDebug() << "ListBrick: Numbering added at cursor position" << cursor.position();
    }
    targetEdit->setTextCursor(cursor);
}
