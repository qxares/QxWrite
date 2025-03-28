#include "tablebrick.h"
#include "placeholderbrick.h"
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
        format.setWidth(QTextLength(QTextLength::PercentageLength, 100));
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

        PlaceholderBrick placeholder(m_textEdit, this);
        placeholder.insertPlaceholder(cursor.position(), PlaceholderBrick::Table);
        cursor.endEditBlock();
        m_textEdit->setTextCursor(cursor);
        qDebug() << "TableBrick: Inserted" << rows << "x" << cols << "table with placeholder";
    }
}
