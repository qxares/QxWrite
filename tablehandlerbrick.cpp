#include "tablehandlerbrick.h"
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
        QTextDocument *doc = m_textEdit->document();
        cursor.setPosition(0);
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

void TableHandlerBrick::deleteTable() {
    QTextTable *table = findTableInDocument();
    if (!table) {
        qDebug() << "TableHandlerBrick: No table found to delete";
        return;
    }

    QTextCursor cursor = table->firstCursorPosition();
    cursor.beginEditBlock();
    int rows = table->rows();
    int cols = table->columns();
    cursor.movePosition(QTextCursor::NextBlock, QTextCursor::KeepAnchor, rows * cols);
    cursor.removeSelectedText();
    cursor.endEditBlock();
    m_textEdit->setTextCursor(cursor);
    qDebug() << "TableHandlerBrick: Table deleted (" << rows << "x" << cols << ")";
}
