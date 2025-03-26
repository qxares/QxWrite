#include "italicbrick.h"
#include <QDebug>

ItalicBrick::ItalicBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    qDebug() << "ItalicBrick initialized with textEdit:" << m_textEdit;
}

void ItalicBrick::applyItalic() {
    if (m_textEdit) {
        QTextCharFormat format = m_textEdit->currentCharFormat();
        format.setFontItalic(!format.fontItalic());
        m_textEdit->mergeCurrentCharFormat(format);
    }
}

void ItalicBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    qDebug() << "ItalicBrick: TextEdit updated to:" << m_textEdit;
}
