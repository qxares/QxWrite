#include "colorbrick.h"
#include <QColorDialog>
#include <QTextCharFormat>
#include <QDebug>

ColorBrick::ColorBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    qDebug() << "ColorBrick initialized with textEdit:" << m_textEdit;
}

void ColorBrick::changeColor() {
    if (m_textEdit) {
        QColor color = QColorDialog::getColor(m_textEdit->textColor(), m_textEdit->parentWidget());
        if (color.isValid()) {
            m_textEdit->setTextColor(color);
            qDebug() << "ColorBrick: Changed color to" << color.name();
        } else {
            qDebug() << "ColorBrick: Color dialog cancelled";
        }
    } else {
        qDebug() << "ColorBrick: No text edit available";
    }
}
