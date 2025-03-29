#include "alignbrick.h"
#include <QTextCursor>
#include <QTextTable>
#include <QDebug>

AlignBrick::AlignBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    qDebug() << "AlignBrick initialized with textEdit:" << m_textEdit;
}

void AlignBrick::align(Qt::Alignment alignment) {
    if (!m_textEdit) return;

    QTextCursor cursor = m_textEdit->textCursor();
    cursor.beginEditBlock();

    QTextTable *table = cursor.currentTable();
    if (table) {
        QTextTableFormat format = table->format();
        format.setAlignment(alignment);
        table->setFormat(format);
        qDebug() << "AlignBrick: Table aligned to" << (alignment == Qt::AlignLeft ? "left" :
                                                       alignment == Qt::AlignCenter ? "center" : "right");
    } else {
        m_textEdit->setAlignment(alignment);
        qDebug() << "AlignBrick: Text aligned to" << (alignment == Qt::AlignLeft ? "left" :
                                                      alignment == Qt::AlignCenter ? "center" : "right");
    }

    cursor.endEditBlock();
}

void AlignBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    qDebug() << "AlignBrick: TextEdit updated to:" << m_textEdit;
}
