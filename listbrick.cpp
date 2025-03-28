#include "listbrick.h"
#include <QTextCursor>
#include <QTextList>
#include <QTextListFormat>
#include <QDebug>

ListBrick::ListBrick(QTextEdit *textEdit, QObject *parent) : QObject(parent), m_textEdit(textEdit) {}

void ListBrick::setTextEdit(QTextEdit *textEdit) {
    m_textEdit = textEdit;
}

void ListBrick::toggleNumbering() {
    if (!m_textEdit) {
        qDebug() << "ListBrick: No text edit set for numbering";
        return;
    }

    QTextCursor cursor = m_textEdit->textCursor();
    QTextList *list = cursor.currentList();

    if (list && list->format().style() == QTextListFormat::ListDecimal) {
        // Remove list if it's already numbered
        cursor.beginEditBlock();
        QTextBlock block = cursor.block();
        list->remove(block);
        cursor.endEditBlock();
    } else {
        // Add numbered list
        cursor.beginEditBlock();
        QTextListFormat listFormat;
        listFormat.setStyle(QTextListFormat::ListDecimal);
        cursor.createList(listFormat);
        cursor.endEditBlock();
    }

    m_textEdit->setTextCursor(cursor);
}

void ListBrick::toggleBullets() {
    if (!m_textEdit) {
        qDebug() << "ListBrick: No text edit set for bullets";
        return;
    }

    QTextCursor cursor = m_textEdit->textCursor();
    QTextList *list = cursor.currentList();

    if (list && list->format().style() == QTextListFormat::ListDisc) {
        // Remove list if it's already bulleted
        cursor.beginEditBlock();
        QTextBlock block = cursor.block();
        list->remove(block);
        cursor.endEditBlock();
    } else {
        // Add bulleted list
        cursor.beginEditBlock();
        QTextListFormat listFormat;
        listFormat.setStyle(QTextListFormat::ListDisc);
        cursor.createList(listFormat);
        cursor.endEditBlock();
    }

    m_textEdit->setTextCursor(cursor);
}
