#include "tablehandlerbrick.h"
#include <QTextCursor>
#include <QTextTable>
#include <QDebug>

TableHandlerBrick::TableHandlerBrick(QTextEdit *textEdit, QObject *parent) : QObject(parent), m_textEdit(textEdit) {}

void TableHandlerBrick::setTextEdit(QTextEdit *textEdit) {
    m_textEdit = textEdit;
}

QTextTable* TableHandlerBrick::findTableAtCursor() {
    if (!m_textEdit) return nullptr;

    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();

    if (!table) {
        cursor.movePosition(QTextCursor::Start);
        while (!cursor.isNull() && !cursor.atEnd()) {
            table = cursor.currentTable();
            if (table) break;
            cursor.movePosition(QTextCursor::NextBlock);
        }
    }
    return table;
}

void TableHandlerBrick::alignTable(Qt::Alignment alignment) {
    QTextTable *table = findTableAtCursor();
    if (!table) {
        qDebug() << "TableHandlerBrick: No table found for alignment";
        return;
    }

    QTextCursor cursor = m_textEdit->textCursor();
    cursor.beginEditBlock();
    QTextTableFormat format = table->format();
    format.setAlignment(alignment);
    table->setFormat(format);

    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(alignment);
    cursor.setBlockFormat(blockFormat);

    cursor.endEditBlock();
    m_textEdit->viewport()->update(); // Force repaint
    qDebug() << "TableHandlerBrick: Aligned table to" << (alignment == Qt::AlignLeft ? "left" : 
                                                         alignment == Qt::AlignCenter ? "center" : "right");
}

void TableHandlerBrick::alignTableLeft() { alignTable(Qt::AlignLeft); }
void TableHandlerBrick::alignTableCenter() { alignTable(Qt::AlignCenter); }
void TableHandlerBrick::alignTableRight() { alignTable(Qt::AlignRight); }

void TableHandlerBrick::deleteTable() {
    QTextTable *table = findTableAtCursor();
    if (!table) {
        qDebug() << "TableHandlerBrick: No table found to delete";
        return;
    }

    QTextCursor cursor = table->firstCursorPosition();
    cursor.beginEditBlock();
    cursor.movePosition(QTextCursor::NextBlock, QTextCursor::KeepAnchor, table->rows() * table->columns());
    cursor.removeSelectedText();
    cursor.endEditBlock();
    m_textEdit->setTextCursor(cursor);
    qDebug() << "TableHandlerBrick: Table deleted";
}
