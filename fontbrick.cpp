#include "fontbrick.h"
#include <QFontDialog>
#include <QDebug>

FontBrick::FontBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    qDebug() << "FontBrick initialized with textEdit:" << m_textEdit;
}

void FontBrick::changeFont() {
    if (m_textEdit) {
        bool ok;
        QFont font = QFontDialog::getFont(&ok, m_textEdit->currentFont(), m_textEdit->parentWidget());
        if (ok) m_textEdit->setCurrentFont(font);
    }
}

void FontBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    qDebug() << "FontBrick: TextEdit updated to:" << m_textEdit;
}
