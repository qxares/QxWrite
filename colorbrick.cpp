#include "colorbrick.h"
#include <QColorDialog>
#include <QDebug>

ColorBrick::ColorBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    qDebug() << "ColorBrick initialized with textEdit:" << m_textEdit;
}

void ColorBrick::changeColor() {
    if (m_textEdit) {
        QColor color = QColorDialog::getColor(m_textEdit->textColor(), m_textEdit->parentWidget());
        if (color.isValid()) m_textEdit->setTextColor(color);
    }
}

void ColorBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    qDebug() << "ColorBrick: TextEdit updated to:" << m_textEdit;
}
