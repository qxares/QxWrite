#include "tablebrick.h"
#include <QTextCursor>
#include <QTextTable>
#include <QTextTableFormat>
#include <QInputDialog>
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

TableBrick::TableBrick(QTextEdit *edit, QObject *parent) : QObject(parent), targetEdit(edit) {
    qDebug() << "TableBrick initialized, target edit:" << targetEdit;
}

void TableBrick::setTextEdit(QTextEdit *edit) {
    targetEdit = edit;
    qDebug() << "TableBrick: TextEdit updated to:" << targetEdit;
}

void TableBrick::insertTable() {
    if (targetEdit) {
        bool ok;
        int rows = QInputDialog::getInt(nullptr, "Insert Table", "Rows:", 2, 1, 100, 1, &ok);
        if (!ok) return;
        int cols = QInputDialog::getInt(nullptr, "Insert Table", "Columns:", 2, 1, 100, 1, &ok);
        if (!ok) return;

        QTextCursor cursor = targetEdit->textCursor();
        QTextTableFormat tableFormat;
        QVector<QTextLength> constraints;
        for (int i = 0; i < cols; ++i) {
            constraints.append(QTextLength(QTextLength::FixedLength, 20 * targetEdit->fontMetrics().averageCharWidth()));
        }
        tableFormat.setColumnWidthConstraints(constraints);
        QTextTable *table = cursor.insertTable(rows, cols, tableFormat);
        if (table) {
            qDebug() << "TableBrick: Table inserted with" << rows << "rows and" << cols << "columns, width set to 20 chars";
        } else {
            qDebug() << "TableBrick: Failed to insert table";
        }
    } else {
        qDebug() << "TableBrick: No target edit set for table insertion";
    }
}

QTextTable* TableBrick::getCurrentTable() {
    if (!targetEdit) return nullptr;
    QTextCursor cursor = targetEdit->textCursor();
    return cursor.currentTable();
}

void TableBrick::addRowBefore() {
    QTextTable *table = getCurrentTable();
    if (table) {
        QTextCursor cursor = targetEdit->textCursor();
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid()) {
            table->insertRows(cell.row(), 1);
            qDebug() << "TableBrick: Added row before row" << cell.row();
        } else {
            qDebug() << "TableBrick: No valid cell selected for row insertion";
        }
    } else {
        qDebug() << "TableBrick: No table at cursor to add row";
    }
}

void TableBrick::addRowAfter() {
    QTextTable *table = getCurrentTable();
    if (table) {
        QTextCursor cursor = targetEdit->textCursor();
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid()) {
            table->insertRows(cell.row() + 1, 1);
            qDebug() << "TableBrick: Added row after row" << cell.row();
        } else {
            qDebug() << "TableBrick: No valid cell selected for row insertion";
        }
    } else {
        qDebug() << "TableBrick: No table at cursor to add row";
    }
}

void TableBrick::addColumnBefore() {
    QTextTable *table = getCurrentTable();
    if (table) {
        QTextCursor cursor = targetEdit->textCursor();
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid()) {
            table->insertColumns(cell.column(), 1);
            qDebug() << "TableBrick: Added column before column" << cell.column();
        } else {
            qDebug() << "TableBrick: No valid cell selected for column insertion";
        }
    } else {
        qDebug() << "TableBrick: No table at cursor to add column";
    }
}

void TableBrick::addColumnAfter() {
    QTextTable *table = getCurrentTable();
    if (table) {
        QTextCursor cursor = targetEdit->textCursor();
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid()) {
            table->insertColumns(cell.column() + 1, 1);
            qDebug() << "TableBrick: Added column after column" << cell.column();
        } else {
            qDebug() << "TableBrick: No valid cell selected for column insertion";
        }
    } else {
        qDebug() << "TableBrick: No table at cursor to add column";
    }
}

void TableBrick::deleteRow() {
    QTextTable *table = getCurrentTable();
    if (table) {
        QTextCursor cursor = targetEdit->textCursor();
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid()) {
            table->removeRows(cell.row(), 1);
            qDebug() << "TableBrick: Deleted row" << cell.row();
        } else {
            qDebug() << "TableBrick: No valid cell selected for row deletion";
        }
    } else {
        qDebug() << "TableBrick: No table at cursor to delete row";
    }
}

void TableBrick::deleteColumn() {
    QTextTable *table = getCurrentTable();
    if (table) {
        QTextCursor cursor = targetEdit->textCursor();
        QTextTableCell cell = table->cellAt(cursor);
        if (cell.isValid()) {
            table->removeColumns(cell.column(), 1);
            qDebug() << "TableBrick: Deleted column" << cell.column();
        } else {
            qDebug() << "TableBrick: No valid cell selected for column deletion";
        }
    } else {
        qDebug() << "TableBrick: No table at cursor to delete column";
    }
}

void TableBrick::deleteTable() {
    QTextTable *table = getCurrentTable();
    if (table) {
        QTextCursor cursor = targetEdit->textCursor();
        int start = table->firstCursorPosition().position();
        int end = table->lastCursorPosition().position();
        cursor.setPosition(start);
        cursor.setPosition(end + 1, QTextCursor::KeepAnchor);
        cursor.removeSelectedText();
        qDebug() << "TableBrick: Deleted entire table";
    } else {
        qDebug() << "TableBrick: No table at cursor to delete";
    }
}

void TableBrick::alignTableLeft() {
    QTextTable *table = getCurrentTable();
    if (table) {
        QTextTableFormat format = table->format();
        format.setAlignment(Qt::AlignLeft);
        table->setFormat(format);
        qDebug() << "TableBrick: Table aligned left";
    } else {
        qDebug() << "TableBrick: No table at cursor to align";
    }
}

void TableBrick::alignTableCenter() {
    QTextTable *table = getCurrentTable();
    if (table) {
        QTextTableFormat format = table->format();
        format.setAlignment(Qt::AlignHCenter);
        table->setFormat(format);
        qDebug() << "TableBrick: Table aligned center";
    } else {
        qDebug() << "TableBrick: No table at cursor to align";
    }
}

void TableBrick::alignTableRight() {
    QTextTable *table = getCurrentTable();
    if (table) {
        QTextTableFormat format = table->format();
        format.setAlignment(Qt::AlignRight);
        table->setFormat(format);
        qDebug() << "TableBrick: Table aligned right";
    } else {
        qDebug() << "TableBrick: No table at cursor to align";
    }
}

void TableBrick::mergeCells() {
    QTextTable *table = getCurrentTable();
    if (table) {
        QTextCursor cursor = targetEdit->textCursor();
        if (cursor.hasSelection()) {
            table->mergeCells(cursor);
            qDebug() << "TableBrick: Selected cells merged";
        } else {
            qDebug() << "TableBrick: No selection to merge cells";
        }
    } else {
        qDebug() << "TableBrick: No table at cursor to merge cells";
    }
}

void TableBrick::splitCells() {
    QTextTable *table = getCurrentTable();
    if (!table) {
        qDebug() << "TableBrick: No table at cursor to split cells";
        return;
    }

    QTextCursor cursor = targetEdit->textCursor();
    QTextTableCell cell = table->cellAt(cursor);
    if (!cell.isValid()) {
        qDebug() << "TableBrick: No valid cell selected to split";
        return;
    }

    // Check if the cell is merged (spans > 1 row or column)
    int rowSpan = cell.rowSpan();
    int colSpan = cell.columnSpan();
    if (rowSpan <= 1 && colSpan <= 1) {
        qDebug() << "TableBrick: Cell at row" << cell.row() << "column" << cell.column() << "is not merged, cannot split";
        return;
    }

    QDialog *splitDialog = new QDialog(nullptr);
    splitDialog->setWindowTitle("Split Cell");
    QVBoxLayout *layout = new QVBoxLayout(splitDialog);

    QLabel *rowLabel = new QLabel("Rows (max " + QString::number(rowSpan) + "):");
    QComboBox *rowCombo = new QComboBox();
    for (int i = 1; i <= rowSpan; ++i) {
        rowCombo->addItem(QString::number(i));
    }
    rowCombo->setCurrentIndex(rowSpan > 1 ? 1 : 0); // Default to 2 if possible

    QLabel *colLabel = new QLabel("Columns (max " + QString::number(colSpan) + "):");
    QComboBox *colCombo = new QComboBox();
    for (int i = 1; i <= colSpan; ++i) {
        colCombo->addItem(QString::number(i));
    }
    colCombo->setCurrentIndex(colSpan > 1 ? 1 : 0); // Default to 2 if possible

    QPushButton *okButton = new QPushButton("OK");
    connect(okButton, &QPushButton::clicked, splitDialog, &QDialog::accept);

    layout->addWidget(rowLabel);
    layout->addWidget(rowCombo);
    layout->addWidget(colLabel);
    layout->addWidget(colCombo);
    layout->addWidget(okButton);
    splitDialog->setLayout(layout);

    if (splitDialog->exec() == QDialog::Accepted) {
        int rows = rowCombo->currentText().toInt();
        int cols = colCombo->currentText().toInt();
        if ((rows > 1 || cols > 1) && rows <= rowSpan && cols <= colSpan) {
            table->splitCell(cell.row(), cell.column(), rows, cols);
            targetEdit->update(); // Force redraw
            qDebug() << "TableBrick: Cell at row" << cell.row() << "column" << cell.column() << "split into" << rows << "rows and" << cols << "columns";
        } else {
            qDebug() << "TableBrick: Invalid split dimensions (rows:" << rows << ", cols:" << cols << ") for span (rows:" << rowSpan << ", cols:" << colSpan << ")";
        }
    } else {
        qDebug() << "TableBrick: Split cell dialog canceled";
    }
    delete splitDialog;
}
