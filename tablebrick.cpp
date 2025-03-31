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
        format.setAlignment(Qt::AlignLeft);
        QVector<QTextLength> constraints;
        for (int col = 0; col < cols; ++col) {
            constraints.append(QTextLength(QTextLength::FixedLength, 120));
        }
        format.setColumnWidthConstraints(constraints);
        table->setFormat(format);

        QTextCharFormat cellFormat;
        cellFormat.setProperty(QTextFormat::BlockBottomMargin, 30);
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                QTextTableCell cell = table->cellAt(row, col);
                QTextCursor cellCursor = cell.firstCursorPosition();
                cellCursor.mergeBlockCharFormat(cellFormat);
            }
        }

        QTextBlockFormat blockFormat;
        blockFormat.setAlignment(Qt::AlignLeft);
        cursor.setBlockFormat(blockFormat);

        cursor.endEditBlock();
        m_textEdit->setTextCursor(cursor);
        qDebug() << "TableBrick: Inserted" << rows << "x" << cols << "table with 120px wide, 30px tall cells";
    }
}

void TableBrick::insertRowBefore() {
    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (!table) {
        qDebug() << "TableBrick: No table at cursor to insert row before";
        return;
    }
    int row = cursor.currentTable()->cellAt(cursor).row();
    cursor.beginEditBlock();
    table->insertRows(row, 1);
    cursor.endEditBlock();
    qDebug() << "TableBrick: Inserted row before row" << row;
}

void TableBrick::insertRowAfter() {
    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (!table) {
        qDebug() << "TableBrick: No table at cursor to insert row after";
        return;
    }
    int row = cursor.currentTable()->cellAt(cursor).row() + 1;
    cursor.beginEditBlock();
    table->insertRows(row, 1);
    cursor.endEditBlock();
    qDebug() << "TableBrick: Inserted row after row" << (row - 1);
}

void TableBrick::insertRowAbove() { insertRowBefore(); } // Alias for clarity
void TableBrick::insertRowBelow() { insertRowAfter(); }  // Alias for clarity

void TableBrick::insertColumnBefore() {
    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (!table) {
        qDebug() << "TableBrick: No table at cursor to insert column before";
        return;
    }
    int col = cursor.currentTable()->cellAt(cursor).column();
    cursor.beginEditBlock();
    table->insertColumns(col, 1);
    QTextTableFormat format = table->format();
    QVector<QTextLength> constraints = format.columnWidthConstraints();
    constraints.insert(col, QTextLength(QTextLength::FixedLength, 120));
    format.setColumnWidthConstraints(constraints);
    table->setFormat(format);
    cursor.endEditBlock();
    qDebug() << "TableBrick: Inserted column before column" << col;
}

void TableBrick::insertColumnAfter() {
    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (!table) {
        qDebug() << "TableBrick: No table at cursor to insert column after";
        return;
    }
    int col = cursor.currentTable()->cellAt(cursor).column() + 1;
    cursor.beginEditBlock();
    table->insertColumns(col, 1);
    QTextTableFormat format = table->format();
    QVector<QTextLength> constraints = format.columnWidthConstraints();
    constraints.insert(col, QTextLength(QTextLength::FixedLength, 120));
    format.setColumnWidthConstraints(constraints);
    table->setFormat(format);
    cursor.endEditBlock();
    qDebug() << "TableBrick: Inserted column after column" << (col - 1);
}

void TableBrick::insertColumnAbove() { insertColumnBefore(); } // Alias
void TableBrick::insertColumnBelow() { insertColumnAfter(); }  // Alias

void TableBrick::deleteRow() {
    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (!table) {
        qDebug() << "TableBrick: No table at cursor to delete row";
        return;
    }
    int row = cursor.currentTable()->cellAt(cursor).row();
    cursor.beginEditBlock();
    table->removeRows(row, 1);
    cursor.endEditBlock();
    qDebug() << "TableBrick: Deleted row" << row;
}

void TableBrick::deleteColumn() {
    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (!table) {
        qDebug() << "TableBrick: No table at cursor to delete column";
        return;
    }
    int col = cursor.currentTable()->cellAt(cursor).column();
    cursor.beginEditBlock();
    table->removeColumns(col, 1);
    cursor.endEditBlock();
    qDebug() << "TableBrick: Deleted column" << col;
}

void TableBrick::mergeCells() {
    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (!table) {
        qDebug() << "TableBrick: No table at cursor to merge cells";
        return;
    }
    if (!cursor.hasSelection()) {
        qDebug() << "TableBrick: No cell selection to merge";
        return;
    }
    QTextTableCell startCell = table->cellAt(cursor.selectionStart());
    QTextTableCell endCell = table->cellAt(cursor.selectionEnd());
    int firstRow = startCell.row();
    int firstCol = startCell.column();
    int numRows = endCell.row() - firstRow + 1;
    int numCols = endCell.column() - firstCol + 1;
    if (numRows > 1 || numCols > 1) {
        cursor.beginEditBlock();
        table->mergeCells(firstRow, firstCol, numRows, numCols);
        cursor.endEditBlock();
        qDebug() << "TableBrick: Merged" << numRows << "rows and" << numCols << "columns at" << firstRow << "," << firstCol;
    } else {
        qDebug() << "TableBrick: Selection too small to merge";
    }
}

void TableBrick::deleteTable() {} // Handled by TableHandlerBrick
void TableBrick::alignTableLeft() {} // Handled by TableHandlerBrick
void TableBrick::alignTableCenter() {} // Handled by TableHandlerBrick
void TableBrick::alignTableRight() {} // Handled by TableHandlerBrick
