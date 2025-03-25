#include "italicbrick.h"
#include <QTextCharFormat>
#include <QDebug>

ItalicBrick::ItalicBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    qDebug() << "ItalicBrick initialized with textEdit:" << m_textEdit;
}

void ItalicBrick::applyItalic() {
    if (m_textEdit) {
        QTextCharFormat format = m_textEdit->currentCharFormat();
        format.setFontItalic(!format.fontItalic());
        m_textEdit->mergeCurrentCharFormat(format);
        qDebug() << "ItalicBrick: Toggled italic";
    } else {
        qDebug() << "ItalicBrick: No text edit available";
    }
}
