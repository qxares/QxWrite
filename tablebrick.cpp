#include "tablebrick.h"
#include <QTextCursor>
#include <QTextTable>
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

TableBrick::TableBrick(QTextEdit *textEdit, QObject *parent) : QObject(parent), m_textEdit(textEdit) {}

void TableBrick::setTextEdit(QTextEdit *textEdit) {
    m_textEdit = textEdit;
}

void TableBrick::insertTable() {
    if (!m_textEdit) {
        qDebug() << "TableBrick: No text edit set for table insertion";
        return;
    }

    QDialog dialog;
    dialog.setWindowTitle("Insert Table");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QHBoxLayout *rowLayout = new QHBoxLayout();
    QLabel *rowLabel = new QLabel("Rows:");
    QSpinBox *rowSpin = new QSpinBox();
    rowSpin->setRange(1, 100);
    rowSpin->setValue(3);
    rowLayout->addWidget(rowLabel);
    rowLayout->addWidget(rowSpin);

    QHBoxLayout *colLayout = new QHBoxLayout();
    QLabel *colLabel = new QLabel("Columns:");
    QSpinBox *colSpin = new QSpinBox();
    colSpin->setRange(1, 100);
    colSpin->setValue(3);
    colLayout->addWidget(colLabel);
    colLayout->addWidget(colSpin);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *okButton = new QPushButton("OK");
    QPushButton *cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    layout->addLayout(rowLayout);
    layout->addLayout(colLayout);
    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        int rows = rowSpin->value();
        int cols = colSpin->value();

        QTextCursor cursor = m_textEdit->textCursor();
        cursor.beginEditBlock();
        QTextTable *table = cursor.insertTable(rows, cols);
        QTextTableFormat format;
        format.setCellPadding(5);
        format.setCellSpacing(2);
        format.setBorder(1);
        // Set column widths to 120px
        QVector<QTextLength> constraints;
        for (int col = 0; col < cols; ++col) {
            constraints.append(QTextLength(QTextLength::FixedLength, 120));
        }
        format.setColumnWidthConstraints(constraints);
        table->setFormat(format);

        // Set row heights to 30px by adjusting each cell's format
        QTextCharFormat cellFormat;
        cellFormat.setProperty(QTextFormat::BlockBottomMargin, 30); // Forces minimum height
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                QTextTableCell cell = table->cellAt(row, col);
                QTextCursor cellCursor = cell.firstCursorPosition();
                cellCursor.mergeBlockCharFormat(cellFormat);
            }
        }

        cursor.endEditBlock();
        m_textEdit->setTextCursor(cursor);
        qDebug() << "TableBrick: Inserted" << rows << "x" << cols << "table with 120px wide, 30px tall cells";
    }
}

void TableBrick::insertRowBefore() {
    if (!m_textEdit) return;
    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (table) {
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid()) {
            int row = cell.row();
            table->insertRows(row, 1);
            qDebug() << "TableBrick: Inserted row before row" << row;
        } else {
            qDebug() << "TableBrick: Cursor not in a valid table cell";
        }
    } else {
        qDebug() << "TableBrick: No table at cursor for row insertion";
    }
}

void TableBrick::insertRowAfter() {
    if (!m_textEdit) return;
    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (table) {
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid()) {
            int row = cell.row() + 1;
            table->insertRows(row, 1);
            qDebug() << "TableBrick: Inserted row after row" << row - 1;
        } else {
            qDebug() << "TableBrick: Cursor not in a valid table cell";
        }
    } else {
        qDebug() << "TableBrick: No table at cursor for row insertion";
    }
}

void TableBrick::insertRowAbove() {
    insertRowBefore(); // Alias for consistency with menu naming
}

void TableBrick::insertRowBelow() {
    insertRowAfter(); // Alias for consistency with menu naming
}

void TableBrick::insertColumnBefore() {
    if (!m_textEdit) return;
    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (table) {
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid()) {
            int col = cell.column();
            table->insertColumns(col, 1);
            qDebug() << "TableBrick: Inserted column before column" << col;
        } else {
            qDebug() << "TableBrick: Cursor not in a valid table cell";
        }
    } else {
        qDebug() << "TableBrick: No table at cursor for column insertion";
    }
}

void TableBrick::insertColumnAfter() {
    if (!m_textEdit) return;
    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (table) {
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid()) {
            int col = cell.column() + 1;
            table->insertColumns(col, 1);
            qDebug() << "TableBrick: Inserted column after column" << col - 1;
        } else {
            qDebug() << "TableBrick: Cursor not in a valid table cell";
        }
    } else {
        qDebug() << "TableBrick: No table at cursor for column insertion";
    }
}

void TableBrick::insertColumnAbove() {
    insertColumnBefore(); // Alias for consistency
}

void TableBrick::insertColumnBelow() {
    insertColumnAfter(); // Alias for consistency
}

void TableBrick::deleteRow() {
    if (!m_textEdit) return;
    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (table) {
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid()) {
            int row = cell.row();
            table->removeRows(row, 1);
            qDebug() << "TableBrick: Deleted row" << row;
        } else {
            qDebug() << "TableBrick: Cursor not in a valid table cell";
        }
    } else {
        qDebug() << "TableBrick: No table at cursor for row deletion";
    }
}

void TableBrick::deleteColumn() {
    if (!m_textEdit) return;
    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (table) {
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid()) {
            int col = cell.column();
            table->removeColumns(col, 1);
            qDebug() << "TableBrick: Deleted column" << col;
        } else {
            qDebug() << "TableBrick: Cursor not in a valid table cell";
        }
    } else {
        qDebug() << "TableBrick: No table at cursor for column deletion";
    }
}

void TableBrick::mergeCells() {
    if (!m_textEdit) return;
    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (table && cursor.hasSelection()) {
        QTextTableCell firstCell = table->cellAt(cursor.selectionStart());
        QTextTableCell lastCell = table->cellAt(cursor.selectionEnd());
        int firstRow = firstCell.row();
        int firstCol = firstCell.column();
        int rows = lastCell.row() - firstRow + 1;
        int cols = lastCell.column() - firstCol + 1;
        if (rows > 1 || cols > 1) {
            table->mergeCells(firstRow, firstCol, rows, cols);
            qDebug() << "TableBrick: Merged" << rows << "x" << cols << "cells at" << firstRow << "," << firstCol;
        } else {
            qDebug() << "TableBrick: Selection too small to merge";
        }
    } else {
        qDebug() << "TableBrick: No table or selection for merging";
    }
}
