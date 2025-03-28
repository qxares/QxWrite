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
        format.setAlignment(Qt::AlignLeft); // Default alignment
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

void TableBrick::alignTable(Qt::Alignment alignment) {
    if (!m_textEdit) return;

    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();

    // If no table at cursor, search for the nearest one
    if (!table) {
        QTextDocument *doc = m_textEdit->document();
        cursor.movePosition(QTextCursor::Start);
        while (!cursor.isNull() && !cursor.atEnd()) {
            table = cursor.currentTable();
            if (table) break;
            cursor.movePosition(QTextCursor::NextBlock);
        }
    }

    if (table) {
        cursor.beginEditBlock();
        QTextTableFormat format = table->format();
        format.setAlignment(alignment);
        table->setFormat(format);

        QTextBlockFormat blockFormat;
        blockFormat.setAlignment(alignment);
        cursor.setBlockFormat(blockFormat);

        cursor.endEditBlock();
        m_textEdit->update();
        qDebug() << "TableBrick: Aligned table to" << (alignment == Qt::AlignLeft ? "left" : 
                                                      alignment == Qt::AlignCenter ? "center" : "right");
    } else {
        qDebug() << "TableBrick: No table found in document for alignment";
    }
}

void TableBrick::alignTableLeft() { alignTable(Qt::AlignLeft); }
void TableBrick::alignTableCenter() { alignTable(Qt::AlignCenter); }
void TableBrick::alignTableRight() { alignTable(Qt::AlignRight); }

void TableBrick::insertRowBefore() { /* ... */ }
void TableBrick::insertRowAfter() { /* ... */ }
void TableBrick::insertRowAbove() { insertRowBefore(); }
void TableBrick::insertRowBelow() { insertRowAfter(); }
void TableBrick::insertColumnBefore() { /* ... */ }
void TableBrick::insertColumnAfter() { /* ... */ }
void TableBrick::insertColumnAbove() { insertColumnBefore(); }
void TableBrick::insertColumnBelow() { insertColumnAfter(); }
void TableBrick::deleteRow() { /* ... */ }
void TableBrick::deleteColumn() { /* ... */ }
void TableBrick::mergeCells() { /* ... */ }
void TableBrick::deleteTable() { /* ... */ }
