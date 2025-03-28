#include "tablebrick.h"
#include <QTextCursor>
#include <QTextTable>
#include <QDebug>

TableBrick::TableBrick(QTextEdit *textEdit, QObject *parent) : QObject(parent), m_textEdit(textEdit) {}

void TableBrick::setTextEdit(QTextEdit *textEdit) {
    m_textEdit = textEdit;
}

void TableBrick::insertTable() {
    if (!m_textEdit) {
        qDebug() << "TableBrick: No text edit set for table insertion";
        return;
    }

    QTextCursor cursor = m_textEdit->textCursor();
    cursor.beginEditBlock();
    QTextTable *table = cursor.insertTable(3, 3); // Default 3x3 table
    table->setFormat(QTextTableFormat());
    cursor.endEditBlock();

    m_textEdit->setTextCursor(cursor);
    qDebug() << "TableBrick: Inserted 3x3 table";
}
