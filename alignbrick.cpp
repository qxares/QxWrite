#include "alignbrick.h"
#include <QDebug>

AlignBrick::AlignBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    qDebug() << "AlignBrick initialized with textEdit:" << m_textEdit;
}

void AlignBrick::align(Qt::Alignment alignment) {
    if (m_textEdit) m_textEdit->setAlignment(alignment);
}

void AlignBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    qDebug() << "AlignBrick: TextEdit updated to:" << m_textEdit;
}
