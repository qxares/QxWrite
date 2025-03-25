#include "alignbrick.h"
#include <QTextEdit>
#include <QDebug>

AlignBrick::AlignBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    qDebug() << "AlignBrick initialized with textEdit:" << m_textEdit;
}

void AlignBrick::align(Qt::Alignment alignment) {
    if (m_textEdit) {
        m_textEdit->setAlignment(alignment);
        qDebug() << "AlignBrick: Set alignment to" << alignment;
    } else {
        qDebug() << "AlignBrick: No text edit available";
    }
}
