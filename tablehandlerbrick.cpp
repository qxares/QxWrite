#include "tablehandlerbrick.h"
#include "tablebrick.h"
#include <QTextCursor>
#include <QTextTable>
#include <QDebug>

TableHandlerBrick::TableHandlerBrick(QTextEdit *textEdit, QObject *parent) : QObject(parent), m_textEdit(textEdit) {}

void TableHandlerBrick::setTextEdit(QTextEdit *textEdit) {
    m_textEdit = textEdit;
}

QTextTable* TableHandlerBrick::findTableInDocument() {
    if (!m_textEdit) return nullptr;

    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();

    if (!table) {
        cursor.setPosition(0); // Start at beginning
        while (!cursor.atEnd()) {
            table = cursor.currentTable();
            if (table) {
                cursor = table->firstCursorPosition();
                m_textEdit->setTextCursor(cursor);
                break;
            }
            cursor.movePosition(QTextCursor::NextBlock);
        }
    }
    return table;
}

void TableHandlerBrick::alignTable(Qt::Alignment alignment) {
    QTextTable *table = findTableInDocument();
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
    m_textEdit->viewport()->update();
    qDebug() << "TableHandlerBrick: Aligned table to" << (alignment == Qt::AlignLeft ? "left" : 
                                                         alignment == Qt::AlignCenter ? "center" : "right");
}

void TableHandlerBrick::alignTableLeft() { alignTable(Qt::AlignLeft); }
void TableHandlerBrick::alignTableCenter() { alignTable(Qt::AlignCenter); }
void TableHandlerBrick::alignTableRight() { alignTable(Qt::AlignRight); }

void TableHandlerBrick::deleteTable() {
    TableBrick tableBrick(m_textEdit, this);
    tableBrick.deleteTable();
}
