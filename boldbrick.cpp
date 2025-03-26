#include "boldbrick.h"
#include <QDebug>

BoldBrick::BoldBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    qDebug() << "BoldBrick initialized with textEdit:" << m_textEdit;
}

void BoldBrick::applyBold() {
    if (m_textEdit) {
        QTextCharFormat format = m_textEdit->currentCharFormat();
        format.setFontWeight(format.fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
        m_textEdit->mergeCurrentCharFormat(format);
    }
}

void BoldBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    qDebug() << "BoldBrick: TextEdit updated to:" << m_textEdit;
}
