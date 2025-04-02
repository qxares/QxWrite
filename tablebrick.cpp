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

void TableBrick::splitCells() {
    if (!m_textEdit) {
        qDebug() << "TableBrick: No text edit set to split cells";
        return;
    }

    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (!table) {
        qDebug() << "TableBrick: No table at cursor to split cells";
        return;
    }

    int maxRows = table->rows();
    int maxCols = table->columns();

    QDialog dialog;
    dialog.setWindowTitle("Split Cell");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QHBoxLayout *rowPosLayout = new QHBoxLayout();
    QLabel *rowPosLabel = new QLabel("Row (0-based):");
    QSpinBox *rowPosSpin = new QSpinBox();
    rowPosSpin->setRange(0, maxRows - 1);
    rowPosSpin->setValue(0); // Default to top row
    rowPosLayout->addWidget(rowPosLabel);
    rowPosLayout->addWidget(rowPosSpin);

    QHBoxLayout *colPosLayout = new QHBoxLayout();
    QLabel *colPosLabel = new QLabel("Column (0-based):");
    QSpinBox *colPosSpin = new QSpinBox();
    colPosSpin->setRange(0, maxCols - 1);
    colPosSpin->setValue(0); // Default to left column
    colPosLayout->addWidget(colPosLabel);
    colPosLayout->addWidget(colPosSpin);

    QHBoxLayout *rowSplitLayout = new QHBoxLayout();
    QLabel *rowSplitLabel = new QLabel("Split into Rows:");
    QSpinBox *rowSplitSpin = new QSpinBox();
    rowSplitSpin->setRange(1, 1); // Will adjust dynamically
    rowSplitSpin->setValue(1);
    rowSplitLayout->addWidget(rowSplitLabel);
    rowSplitLayout->addWidget(rowSplitSpin);

    QHBoxLayout *colSplitLayout = new QHBoxLayout();
    QLabel *colSplitLabel = new QLabel("Split into Columns:");
    QSpinBox *colSplitSpin = new QSpinBox();
    colSplitSpin->setRange(1, 1); // Will adjust dynamically
    colSplitSpin->setValue(1);
    colSplitLayout->addWidget(colSplitLabel);
    colSplitLayout->addWidget(colSplitSpin);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *okButton = new QPushButton("OK");
    QPushButton *cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    layout->addLayout(rowPosLayout);
    layout->addLayout(colPosLayout);
    layout->addLayout(rowSplitLayout);
    layout->addLayout(colSplitLayout);
    layout->addLayout(buttonLayout);

    // Dynamically update split ranges based on selected cell
    auto updateSplitRanges = [table, rowPosSpin, colPosSpin, rowSplitSpin, colSplitSpin]() {
        int row = rowPosSpin->value();
        int col = colPosSpin->value();
        QTextTableCell cell = table->cellAt(row, col);
        int rowSpan = cell.rowSpan();
        int colSpan = cell.columnSpan();
        rowSplitSpin->setRange(1, rowSpan);
        rowSplitSpin->setValue(rowSpan); // Default to max
        colSplitSpin->setRange(1, colSpan);
        colSplitSpin->setValue(colSpan); // Default to max
    };

    connect(rowPosSpin, QOverload<int>::of(&QSpinBox::valueChanged), updateSplitRanges);
    connect(colPosSpin, QOverload<int>::of(&QSpinBox::valueChanged), updateSplitRanges);
    updateSplitRanges(); // Initial call to set ranges

    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        int row = rowPosSpin->value();
        int col = colPosSpin->value();
        int numRows = rowSplitSpin->value();
        int numCols = colSplitSpin->value();

        QTextTableCell cell = table->cellAt(row, col);
        int rowSpan = cell.rowSpan();
        int colSpan = cell.columnSpan();

        if (rowSpan <= 1 && colSpan <= 1) {
            qDebug() << "TableBrick: Cell at" << row << "," << col << "is not merged, cannot split";
            return;
        }

        if (numRows <= rowSpan && numCols <= colSpan) {
            cursor.beginEditBlock();
            table->splitCell(row, col, numRows, numCols);
            cursor.endEditBlock();
            m_textEdit->viewport()->update(); // Force UI refresh
            qDebug() << "TableBrick: Split cell at" << row << "," << col << "from" << rowSpan << "x" << colSpan << "to" << numRows << "x" << numCols;
        } else {
            qDebug() << "TableBrick: Invalid split dimensions" << numRows << "x" << numCols << "exceed" << rowSpan << "x" << colSpan;
        }
    } else {
        qDebug() << "TableBrick: Split cell canceled";
    }
}

void TableBrick::deleteTable() {
    if (!m_textEdit) {
        qDebug() << "TableBrick: No text edit set to delete table";
        return;
    }

    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    
    if (!table) {
        cursor.setPosition(0); // Start at beginning
        while (!cursor.atEnd()) {
            table = cursor.currentTable();
            if (table) {
                break;
            }
            cursor.movePosition(QTextCursor::NextBlock);
        }
    }

    if (!table) {
        qDebug() << "TableBrick: No table found to delete";
        return;
    }

    int rows = table->rows();
    int cols = table->columns();
    cursor.beginEditBlock();
    table->removeRows(0, rows); // Remove all rows to delete the table entirely
    cursor.endEditBlock();
    m_textEdit->setTextCursor(cursor);
    m_textEdit->document()->setModified(true); // Mark document as modified
    m_textEdit->viewport()->update(); // Force UI refresh
    qDebug() << "TableBrick: Table deleted (" << rows << "x" << cols << ")";
}

void TableBrick::alignTableLeft() {} // Handled by TableHandlerBrick
void TableBrick::alignTableCenter() {} // Handled by TableHandlerBrick
void TableBrick::alignTableRight() {} // Handled by TableHandlerBrick
